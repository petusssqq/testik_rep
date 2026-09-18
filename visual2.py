import matplotlib.pyplot as plt
from matplotlib.patches import FancyArrowPatch, Rectangle

plt.rcParams["font.family"] = "serif"
plt.rcParams["font.serif"] = ["Times New Roman"] + plt.rcParams["font.serif"]

# Список смежности для N=5
adj_list = {0: [1], 1: [0, 2], 2: [1, 3], 3: [2, 4], 4: [3]}

fig, ax = plt.subplots(figsize=(8, 5))
ax.set_xlim(-0.5, 6.5)
ax.set_ylim(-1, 6)
ax.axis("off")

box_w, box_h = 1.0, 0.6


def draw_node_box(x, y, text):
    rect = Rectangle(
        (x - box_w / 2, y - box_h / 2),
        box_w,
        box_h,
        facecolor="#f9f9f9",
        edgecolor="black",
        linewidth=1.5,
    )
    ax.add_patch(rect)
    ax.text(x, y, str(text), ha="center", va="center", fontsize=14, family="serif")


def draw_arrow(x1, y1, x2, y2):
    arrow = FancyArrowPatch(
        (x1 + box_w / 2, y1),
        (x2 - box_w / 2, y2),
        arrowstyle="-|>",
        mutation_scale=15,
        color="black",
        linewidth=1.2,
    )
    ax.add_patch(arrow)


# Отрисовка структуры
for vertex in range(5):
    y_pos = 4 - vertex
    draw_node_box(0, y_pos, vertex)

    neighbors = adj_list[vertex]
    for idx, neighbor in enumerate(neighbors):
        x_pos = 2 + idx * 2
        if idx == 0:
            draw_arrow(0, y_pos, x_pos, y_pos)
        else:
            draw_arrow(x_pos - 2, y_pos, x_pos, y_pos)
        draw_node_box(x_pos, y_pos, neighbor)

plt.title(
    "Рисунок 9 — Списки смежности графа N=5 в виде связных структур",
    fontsize=12,
    y=-0.05,
)
plt.tight_layout()
plt.show()
