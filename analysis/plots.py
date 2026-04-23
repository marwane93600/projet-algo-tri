import os
import pathlib
import pandas as pd
import matplotlib.pyplot as plt

# Chemins relatifs au script (fonctionne depuis n'importe où)
ROOT = pathlib.Path(__file__).parent.parent
DATA_DIR    = ROOT / "data"
FIGURES_DIR = ROOT / "figures"
FIGURES_DIR.mkdir(exist_ok=True)

# =========================
#  Chargement des données
# =========================
df = pd.read_csv(DATA_DIR / "resultats.csv")

# On s'assure qu'il y a bien les colonnes attendues
attendues = {"tri", "taille", "cas", "plage", "temps"}
if not attendues.issubset(df.columns):
    raise ValueError(f"Colonnes manquantes dans resultats.csv, trouvé : {df.columns}")

# Création d'un dossier pour les figures
os.makedirs("figures", exist_ok=True)

# Listes utiles
tris = sorted(df["tri"].unique())
plages = ["petite", "grande"]
# On met les cas dans un ordre logique si possible
ordre_cas = ["croissant", "constant", "aleatoire", "decroissant"]
cas_trouves = list(df["cas"].unique())
cas_list = [c for c in ordre_cas if c in cas_trouves]


# =========================
#  1) Graphes par tri + plage
# =========================
for tri in tris:
    for plage in plages:
        sous_df = df[(df["tri"] == tri) & (df["plage"] == plage)]
        if sous_df.empty:
            continue

        plt.figure()
        for cas in cas_list:
            data_cas = sous_df[sous_df["cas"] == cas]
            if data_cas.empty:
                continue
            plt.plot(
                data_cas["taille"],
                data_cas["temps"],
                marker="o",
                label=cas
            )

        plt.title(f"Tri {tri} ({plage})")
        plt.xlabel("Taille du tableau n")
        plt.ylabel("Temps d'exécution (s)")
        plt.legend(title="Cas")
        plt.grid(True, alpha=0.3)
        plt.tight_layout()

        nom_fichier = FIGURES_DIR / f"tri_{tri}_{plage}.png"
        plt.savefig(nom_fichier, dpi=150)
        plt.close()
        print(f"[OK] Sauvegardé : {nom_fichier}")


# =========================
#  2) Comparaison des tris (cas aléatoire)
# =========================
for plage in plages:
    sous_df = df[(df["plage"] == plage) & (df["cas"] == "aleatoire")]
    if sous_df.empty:
        continue

    plt.figure()
    for tri in tris:
        data_tri = sous_df[sous_df["tri"] == tri]
        if data_tri.empty:
            continue
        plt.plot(
            data_tri["taille"],
            data_tri["temps"],
            marker="o",
            label=tri
        )

    plt.title(f"Comparaison des tris (cas aléatoire, plage {plage})")
    plt.xlabel("Taille du tableau n")
    plt.ylabel("Temps d'exécution (s)")
    plt.legend(title="Tri", fontsize=8)
    plt.grid(True, alpha=0.3)
    plt.tight_layout()

    nom_fichier = FIGURES_DIR / f"comparaison_aleatoire_{plage}.png"
    plt.savefig(nom_fichier, dpi=150)
    plt.close()
    print(f"[OK] Sauvegardé : {nom_fichier}")


# =========================
#  3) Comptage : effet de la plage
# =========================
df_comptage = df[df["tri"] == "comptage"]
if not df_comptage.empty:
    for cas in cas_list:
        sous_df = df_comptage[df_comptage["cas"] == cas]
        if sous_df.empty:
            continue

        plt.figure()
        for plage in plages:
            data_plage = sous_df[sous_df["plage"] == plage]
            if data_plage.empty:
                continue
            plt.plot(
                data_plage["taille"],
                data_plage["temps"],
                marker="o",
                label=plage
            )

        plt.title(f"Tri par comptage : petite vs grande (cas {cas})")
        plt.xlabel("Taille du tableau n")
        plt.ylabel("Temps d'exécution (s)")
        plt.legend(title="Plage")
        plt.grid(True, alpha=0.3)
        plt.tight_layout()

        nom_fichier = FIGURES_DIR / f"comptage_{cas}.png"
        plt.savefig(nom_fichier, dpi=150)
        plt.close()
        print(f"[OK] Sauvegardé : {nom_fichier}")

print("\n🎉 Tous les graphiques ont été générés dans le dossier 'figures/'")
