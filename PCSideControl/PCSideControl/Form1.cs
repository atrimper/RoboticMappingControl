using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PCSideControl {
    public partial class Form1 : Form {
        public Form1() {
            InitializeComponent();
            this.Width = 750;
            this.Height = 500;
        }

        private Rectangle generateCenterPointRectangle(Point center, Size size) {
            return new Rectangle(center.X - size.Width / 2, center.Y - size.Height / 2, size.Width, size.Height);
        }

        private List<Tuple<double, double>> readMapData() {
            List<Tuple<double, double>> list = new List<Tuple<double, double>>();
            for(int i = 0; i < 360; i++) {
                list.Add(new Tuple<double, double>(11, i));
            }
            return list;
        }

        private void printMap(Graphics g, Point center, Size size) {
            List<Tuple<double, double>> polarCoordinates = readMapData();
            double distance;
            double angle;
            foreach (Tuple<double, double> t in polarCoordinates) {
                distance = t.Item1;
                angle = t.Item2;
                int x = (int) (distance * Defines.DISTANCE_TO_PIXELS * Math.Cos(angle * Math.PI / 180));
                int y = (int) (distance * Defines.DISTANCE_TO_PIXELS * Math.Sin(angle * Math.PI / 180));
                Point wall = new Point(center.X + x, center.Y + y);
                if (Math.Abs(x) < Defines.MAP_SIZE / 2 && Math.Abs(y) < Defines.MAP_SIZE / 2) {
                    g.FillRectangle(Brushes.Black, generateCenterPointRectangle(wall, new Size(Defines.DOT_SIZE, Defines.DOT_SIZE)));
                }
            }
        }

        private void form1_Paint(object sender, PaintEventArgs e) {
            Graphics g = this.CreateGraphics();
            Point topLeft = new Point(Defines.MAP_X, Defines.MAP_Y);
            Point mapCenter = new Point(topLeft.X + Defines.MAP_SIZE / 2, topLeft.Y + Defines.MAP_SIZE / 2);
            Size mapSize = new Size(Defines.MAP_SIZE, Defines.MAP_SIZE);
            g.DrawRectangle(Pens.Black, generateCenterPointRectangle(mapCenter, mapSize));
            g.FillRectangle(Brushes.Red, generateCenterPointRectangle(mapCenter, new Size(Defines.ROBOT_SIZE, Defines.ROBOT_SIZE)));
            printMap(g, mapCenter, mapSize);
        }
    }
}
