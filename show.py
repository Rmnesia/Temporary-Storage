import matplotlib.pyplot as plt
import matplotlib.patches as patches
from matplotlib import animation

with open("test") as f:
    s = f.read()
s = s.split('\n')

fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111)

f = open("cal")
move = f.read()
f.close()
move = move.split('\n')

def animate(frame):
    i, j = 0, 0
    pos = move[frame].split(' ')
    for row in s:
        for char in row:
            if char == '*':
                ax.add_patch(patches.Rectangle((j, -i), 0.9, 0.9, color='red'))
            else:
                ax.add_patch(patches.Rectangle((j, -i), 0.9, 0.9, color='black'))
                if (i, j) == (int(pos[0]), int(pos[1])):
                    ax.add_patch(patches.Circle((j+0.5, -i+0.5), 0.3))
            j+=1
        j=0
        i+=1
    ax.autoscale_view()
    return ax

anim = animation.FuncAnimation(fig, animate, frames=60000, interval=300)
plt.axis('off')
plt.show()
