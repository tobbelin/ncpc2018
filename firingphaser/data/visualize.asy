settings.outformat="png";
size(1000);
defaultpen(1);

pen room_types[] = {black, magenta};

int n = stdin;
path room[];
pair pts[];

for (int i = 0; i < n; ++i) {
    real x1 = stdin, y1 = stdin, x2 = stdin, y2 = stdin;
    int b = stdin;
    if (b == 1) {
        fill((x1,y1)--(x2,y1)--(x2,y2)--(x1,y2)--cycle, lightblue);
        draw((x1,y1)--(x2,y1)--(x2,y2)--(x1,y2)--cycle, blue);
    } else {
        fill((x1,y1)--(x2,y1)--(x2,y2)--(x1,y2)--cycle, gray);
        draw((x1,y1)--(x2,y1)--(x2,y2)--(x1,y2)--cycle, black);
    }
}

real x1 = stdin, y1 = stdin, x2 = stdin, y2 = stdin;
draw((x1, y1) -- (x2, y2), p = red+3);

shipout(bbox(xmargin=10, white, Fill));
