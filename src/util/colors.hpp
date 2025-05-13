// Color enumeration
enum Color
{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    WHITE,
    BLACK,
    GOLD,
    PURPLE,
    ORANGE,
    SILVER,
    GRAY,
    PINK,
    CYAN,
    BROWN,
    GOLDENROD,
    SADDLEBROWN,
    INDIGO,
    LIGHT_GREEN,
    DARK_ORANGE,
    DARK_SLATE_GRAY,
    DARK_PURPLE,
    YELLOW_GREEN,
    SLATE_BLUE,
    DARK_GREEN
};

// Definition of the Colors structure
struct Colors
{
    float cor[3];

    // Constructor to facilitate initialization
    Colors(float r, float g, float b)
    {
        cor[0] = r;
        cor[1] = g;
        cor[2] = b;
    }
};

const Colors predefinedColors[] = {
    Colors(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f),     // RED
    Colors(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f),     // GREEN
    Colors(0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f),     // BLUE
    Colors(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f),   // YELLOW
    Colors(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f), // WHITE
    Colors(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f),       // BLACK
    Colors(218.0f / 255.0f, 165.0f / 255.0f, 32.0f / 255.0f),  // GOLD
    Colors(128.0f / 255.0f, 0.0f / 255.0f, 128.0f / 255.0f),   // PURPLE
    Colors(255.0f / 255.0f, 165.0f / 255.0f, 0.0f / 255.0f),   // ORANGE
    Colors(192.0f / 255.0f, 192.0f / 255.0f, 192.0f / 255.0f), // SILVER
    Colors(128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f), // GRAY
    Colors(255.0f / 255.0f, 192.0f / 255.0f, 203.0f / 255.0f), // PINK
    Colors(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f),   // CYAN
    Colors(165.0f / 255.0f, 42.0f / 255.0f, 42.0f / 255.0f),   // BROWN
    Colors(255.0f / 255.0f, 215.0f / 255.0f, 0.0f / 255.0f),   // GOLDENROD
    Colors(139.0f / 255.0f, 69.0f / 255.0f, 19.0f / 255.0f),   // SADDLEBROWN
    Colors(75.0f / 255.0f, 0.0f / 255.0f, 130.0f / 255.0f),    // INDIGO
    Colors(144.0f / 255.0f, 238.0f / 255.0f, 144.0f / 255.0f), // LIGHT GREEN
    Colors(255.0f / 255.0f, 140.0f / 255.0f, 0.0f / 255.0f),   // DARK ORANGE
    Colors(47.0f / 255.0f, 79.0f / 255.0f, 79.0f / 255.0f),    // DARK SLATE GRAY
    Colors(29.0 / 255.0, 13.0 / 255.0, 89.0 / 255.0),          // DARK PURPLE
    Colors(232.0 / 255.0, 232.0 / 255.0, 5.0 / 255.0),         // YELLOW_GREEN
    Colors(106.0f / 255.0f, 90.0f / 255.0f, 205.0f / 255.0f),  // SLATE_BLUE
    Colors(2.0f / 255.0f, 48.0f / 255.0f, 32.0f / 255.0f),  // DARK GREEN
};