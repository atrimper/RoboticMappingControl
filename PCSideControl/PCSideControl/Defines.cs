using System.Drawing;
namespace PCSideControl {
    class Defines {
        public static int MAP_X = 0;
        public static int MAP_Y = 0;
        public static double MAX_DISTANCE = 120.0;
        public static int MAP_SIZE = 200;
        public static int ROBOT_SIZE = 10;
        public static int DOT_SIZE = 2;
        public static int WAYPOINT_SIZE = 4;
        public static double DISTANCE_TO_PIXELS = (MAP_SIZE / 2) / MAX_DISTANCE;

        public static Point topLeft = new Point(Defines.MAP_X, Defines.MAP_Y);
        public static Point mapCenter = new Point(topLeft.X + Defines.MAP_SIZE / 2, topLeft.Y + Defines.MAP_SIZE / 2);
        public static Size mapSize = new Size(Defines.MAP_SIZE, Defines.MAP_SIZE);
    }
}
