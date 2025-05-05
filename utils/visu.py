import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.animation as animation

# Paramètres du domaine
Ld_x = 250
Ld_y = 180
Ld_z = 0

# Lecture du fichier de données
def parse_data(filename):
    with open(filename, 'r') as f:
        content = f.read().strip()
    
    time_steps = content.split('\n\n')
    all_steps = []
    
    for step in time_steps:
        particles = []
        for line in step.strip().split('\n'):
            if not line.strip():
                continue
            x, y, z = map(float, line.strip().split())
            particles.append((x, y, z))
        all_steps.append(particles)
    
    return all_steps

fig = plt.figure(figsize=(10, 6))
ax = fig.add_subplot(111, projection='3d')

def init():
    ax.set_xlim(0, Ld_x)
    ax.set_ylim(0, Ld_y)
    ax.set_zlim(0, Ld_z)
    ax.set_xlabel('X axis')
    ax.set_ylabel('Y axis')
    ax.set_zlabel('Z axis')
    return ax,

def update(frame):
    ax.clear()
    ax.set_xlim(0, Ld_x)
    ax.set_ylim(0, Ld_y)
    ax.set_zlim(0, Ld_z)
    
    particles = data[frame]
    if particles:
        xs = [p[0] for p in particles]
        ys = [p[1] for p in particles]
        zs = [p[2] for p in particles]
        ax.scatter(xs, ys, zs, s=2, c='blue', depthshade=False)
    
    ax.set_title(f't =  {frame}')
    return ax,

# Chargement des données
data = parse_data('p.data') 

# Création de l'animation
ani = animation.FuncAnimation(fig, update, 
                            frames=len(data), 
                            init_func=init, 
                            interval=20, 
                            blit=False)

# Affichage de l'animation
plt.show()