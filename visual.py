import matplotlib.pyplot as plt
import matplotlib.patches as patches

def draw_treapnode_gost():
    # Настройка шрифта без засечек, близкого к чертежному ГОСТ (Arial/DejaVu)
    plt.rcParams['font.sans-serif'] = ['Arial', 'DejaVu Sans', 'Liberation Sans']
    plt.rcParams['font.family'] = 'sans-serif'
    
    # Инициализация холста (черно-белая схема)
    fig, ax = plt.subplots(figsize=(9, 6), facecolor='white')
    ax.set_xlim(0, 10)
    ax.set_ylim(0, 7)
    ax.axis('off')

    # --- 1. Отрисовка основного узла TreapNode (Толстая линия по ГОСТ) ---
    node_x, node_y = 3.5, 2.5
    node_w, node_h = 3.0, 3.2
    
    # Основная рамка (толщина 2.0)
    rect_node = patches.Rectangle((node_x, node_y), node_w, node_h, linewidth=2.0, edgecolor='black', facecolor='none')
    ax.add_patch(rect_node)

    # Горизонтальные тонкие разделители полей (толщина 1.0)
    lines_y = [3.5, 4.5, 5.2]
    for y in lines_y:
        ax.plot([node_x, node_x + node_w], [y, y], color='black', linewidth=1.0)

    # Вертикальный разделитель указателей left / right внизу узла
    ax.plot([node_x + node_w/2, node_x + node_w/2], [node_y, node_y + 1.0], color='black', linewidth=1.0)

    # --- 2. Текстовое наполнение полей (шрифт GOST-style) ---
    ax.text(node_x + 0.1, 5.3, "struct TreapNode", fontsize=11, fontweight='bold', va='bottom', ha='left')
    ax.text(node_x + 0.2, 4.85, "key: long long", fontsize=10, va='center', ha='left')
    ax.text(node_x + 0.2, 4.0, "priority: int", fontsize=10, va='center', ha='left')
    
    # Текст указателей
    ax.text(node_x + node_w/4, 3.0, "left\n(TreapNode*)", fontsize=9, va='center', ha='center')
    ax.text(node_x + 3*node_w/4, 3.0, "right\n(TreapNode*)", fontsize=9, va='center', ha='center')

    # --- 3. Смежные элементы (Дети) ---
    # Блок Левого потомка (Снизу-слева)
    left_x, left_y = 0.5, 0.5
    rect_left = patches.Rectangle((left_x, left_y), node_w, 0.8, linewidth=1.5, edgecolor='black', facecolor='none', linestyle='--')
    ax.add_patch(rect_left)
    ax.text(left_x + node_w/2, left_y + 0.4, "left child: TreapNode", fontsize=10, ha='center', va='center')

    # Блок Правого потомка (Снизу-справа)
    right_x, right_y = 6.5, 0.5
    rect_right = patches.Rectangle((right_x, right_y), node_w, 0.8, linewidth=1.5, edgecolor='black', facecolor='none', linestyle='--')
    ax.add_patch(rect_right)
    ax.text(right_x + node_w/2, right_y + 0.4, "right child: TreapNode", fontsize=10, ha='center', va='center')

    # --- 4. Линии связи со стрелками ---
    # Изломанная линия от left к левому потомку (ГОСТ углы под 90 градусов)
    ax.annotate('', xy=(left_x + node_w/2, left_y + 0.8), xytext=(node_x + node_w/4, node_y),
                arrowprops=dict(arrowstyle="->", color='black', linewidth=1.2, 
                                connectionstyle="angle,angleA=0,angleB=90,rad=0", shrinkA=0, shrinkB=0))

    # Изломанная линия от right к правому потомку
    ax.annotate('', xy=(right_x + node_w/2, right_y + 0.8), xytext=(node_x + 3*node_w/4, node_y),
                arrowprops=dict(arrowstyle="->", color='black', linewidth=1.2, 
                                connectionstyle="angle,angleA=0,angleB=90,rad=0", shrinkA=0, shrinkB=0))

    # Сохранение изображения (высокое разрешение, без полей)
    plt.tight_layout()
    plt.savefig('gost_treapnode_structure.png', dpi=300, bbox_inches='tight')
    plt.close()
    print("Изображение успешно сгенерировано и сохранено в файл: gost_treapnode_structure.png")

if __name__ == "__main__":
    draw_treapnode_gost()
