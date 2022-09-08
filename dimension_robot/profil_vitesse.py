import json
import matplotlib.pyplot as plt
import numpy as np


def creation_profil(temps, num_motor, rapport=3):
    """Modifie le fichier json 'mouvement.json' pour attribuer les vitesse et accélération des moteurs

    Args:
        temps ([int]): [temps nécessaire pour effectuer 360°]
        num_motor ([int]): [indice du moteur]
        rapport (int, optional): [profil de vitesse (2 pour triangle, 3 pour trapèze)]. Defaults to 3.

    Returns:
        [float]: [vitesse et accélération du moteur]
    """
    w = 360 / (temps/rapport + (temps-2*temps/rapport))
    a = w / (temps/rapport)
    with open("mouvement.json") as f:
        data = json.load(f)
    for item in data['motor']:
        if item['id'] == num_motor:
            item['vitesse'] = round(w, 1)
            item['acceleration'] = round(a, 1)
    with open('mouvement.json', 'w') as f:
        json.dump(data, f, indent=4)
    return w, a, temps, num_motor, rapport
        
if __name__ == '__main__':
    w, a, temps, num_motor, rapport = creation_profil(1, 4)
    print(f'La vitesse est : {w:.1f} et l\'accélération est : {a:.1f}')
    x = [0, temps/rapport, temps-(temps/rapport), temps]
    y = [0, w, w, 0]
    fig, ax = plt.subplots()
    plt.title("W = f(t)")
    plt.xlabel("t(s)")
    plt.ylabel("W(°/s)")
    ax.plot(x, y, linewidth=2.0)
    plt.grid()
    plt.show()