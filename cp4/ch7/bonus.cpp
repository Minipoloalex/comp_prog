struct point_i {
  int x, y;                                      // use this if possible
  point_i() { x = y = 0; }                       // default constructor
  point_i(int _x, int _y) : x(_x), y(_y) {}      // constructor
};

struct quad {
    int x_l, x_r, y_b, y_t;
    quad(point_i _bot_left, point_i _top_right) {
        x_l = _bot_left.x; x_r = _top_right.x;
        y_b = _bot_left.y; y_t = _top_right.y;
    }
};
