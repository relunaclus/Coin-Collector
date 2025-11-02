struct Player {
    int x = 400;
    int y = 300;
    int speedX = 3;
    int speedY = 3;
    int points = 5;
    float rad = points + 5;
    int mag = 0;
    int gro = 1;
    float effectiveRad = rad + mag;
    int range = rad/2;
    Color color = BROWN;
};