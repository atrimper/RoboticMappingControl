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

        private void printMap(Graphics g, Point center, Size size) {
            Random r = new Random();
            double xScale = 0;
            double yScale = 0;
            for(int i = 0; i < 360; i++) {
                xScale = 50 * (((r.NextDouble() - 0.5) * 0.5) + 1);
                int x = (int) (xScale * Math.Cos(i * Math.PI / 180));
                yScale = 50 * (((r.NextDouble() - 0.5) * 0.5) + 1);
                int y = (int) (yScale * Math.Sin(i * Math.PI / 180));
                Point wall = new Point(center.X + x, center.Y + y);
                if(xScale < 100 && yScale < 100) {
                    g.FillRectangle(Brushes.Black, generateCenterPointRectangle(wall, new Size(2, 2)));
                }
            }
        }

        private void form1_Paint(object sender, PaintEventArgs e) {
            Graphics g = this.CreateGraphics();
            Point topLeft = new Point(0, 0);
            Point mapCenter = new Point(topLeft.X + 100, topLeft.Y + 100);
            Size mapSize = new Size(200, 200);
            g.DrawRectangle(Pens.Black, generateCenterPointRectangle(mapCenter, mapSize));
            g.FillRectangle(Brushes.Red, generateCenterPointRectangle(mapCenter, new Size(10, 10)));
            printMap(g, mapCenter, mapSize);
        }
    }
}
