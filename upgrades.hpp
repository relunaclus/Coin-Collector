struct Magnet{
    int x = 160;
    int y = 120;
    int scaleX = 50;
    int scaleY = 50;
    Color color = RED;
    int bPrice = 10;
    int inflation = 1;
    int price = bPrice * inflation;
};

struct Growth{
    int x = 320;
    int y = 120;
    int scaleX = 50;
    int scaleY = 50;
    Color color = GREEN;
    int bPrice = 20;
    int inflation = 1;
    int price = bPrice * inflation*inflation;
};

struct Speed{
    int x = 480;
    int y = 120;
    int scaleX = 50;
    int scaleY = 50;
    Color color = SKYBLUE;
    int bPrice = 15;
    int inflation = 1;
    int price = bPrice * inflation * inflation;
};


