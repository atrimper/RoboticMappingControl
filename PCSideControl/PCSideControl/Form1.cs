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
        Graphics g;
        double angle;
        LinkedList<Point> moveList;

        public Form1() {
            InitializeComponent();
            this.Width = 750;
            this.Height = 500;
            moveList = new LinkedList<Point>();
            moveList.AddLast(Defines.mapCenter);
        }

        private Rectangle generateCenterPointRectangle(Point center, Size size) {
            return new Rectangle(center.X - size.Width / 2, center.Y - size.Height / 2, size.Width, size.Height);
        }

        private Point generateMapPoint(double distance, double angle) {
            int x = (int) (distance * Defines.DISTANCE_TO_PIXELS * Math.Cos(angle * Math.PI / 180));
            int y = (int) (distance * Defines.DISTANCE_TO_PIXELS * Math.Sin(angle * Math.PI / 180));
            return new Point(x, y);
        }

        private double pointToPointDistanceFeet(Point a, Point b) {
            double dx = (b.X - a.X) * (1 / Defines.DISTANCE_TO_PIXELS);
            double dy = (b.Y - a.Y) * (1 / Defines.DISTANCE_TO_PIXELS);
            double distance = Math.Sqrt(Math.Pow(dx, 2) + Math.Pow(dy, 2));
            return distance;
        }

        private double pointToPointAngle(Point center, Point point) {
            double dx = point.X - center.X;
            double dy = point.Y - center.Y;
            double angle = 0;
            if(dx == 0) {
                if(dy >= 0) {
                    angle = 0;
                }
                else {
                    angle = 180;
                }
            }
            else {
                angle = 90 + (180.0 / Math.PI) * Math.Atan(dy / dx);
                if(dx < 0) {
                    angle = 180 + angle;
                }
            }
            return angle;
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
            g.DrawRectangle(Pens.Black, generateCenterPointRectangle(Defines.mapCenter, Defines.mapSize));
            g.FillRectangle(Brushes.Red, generateCenterPointRectangle(Defines.mapCenter, new Size(Defines.ROBOT_SIZE, Defines.ROBOT_SIZE)));
            foreach(Tuple<double, double> t in polarCoordinates) {
                distance = t.Item1;
                angle = t.Item2;
                Point pt = generateMapPoint(distance, angle);
                int x = pt.X;
                int y = pt.Y;
                Point wall = new Point(center.X + x, center.Y + y);
                if (Math.Abs(x) < Defines.MAP_SIZE / 2 && Math.Abs(y) < Defines.MAP_SIZE / 2) {
                    g.FillRectangle(Brushes.Black, generateCenterPointRectangle(wall, new Size(Defines.DOT_SIZE, Defines.DOT_SIZE)));
                }
            }
        }

        private void clearMapArea(Graphics g, Point center, Size size) {
            g.FillRectangle(new SolidBrush(this.BackColor), generateCenterPointRectangle(center, size));
        }

        private bool isPointWithinMap(Point center, Size size, Point point) {
            if(((center.X - (size.Width / 2)) < point.X && point.X < (center.X + (size.Width / 2)))
                && ((center.Y - (size.Height / 2)) < point.Y && point.Y < (center.Y + (size.Height / 2)))) {
                return true;
            } else {
                return false;
            }
        }

        private void drawRobotPath(Graphics g) {
            LinkedListNode<Point> cur = moveList.First;
            while(cur != null) {
                if(cur.Next != null) {
                    g.DrawLine(Pens.DarkBlue, cur.Value, cur.Next.Value);
                    g.FillRectangle(Brushes.Red, generateCenterPointRectangle(cur.Next.Value, 
                        new Size(Defines.WAYPOINT_SIZE, Defines.WAYPOINT_SIZE)));
                }
                cur = cur.Next;
            }
        }

        private void appendToMoveList(Point movePoint) {
            if(isPointWithinMap(Defines.mapCenter, Defines.mapSize, movePoint)) {
                moveList.AddLast(movePoint);
            }
        }

        private LinkedList<Tuple<double, double>> moveListToVectorList() {
            LinkedList<Tuple<double, double>> list = new LinkedList<Tuple<double, double>>();
            LinkedListNode<Point> cur = moveList.First;
            double prevAngle = 0.0;
            while(cur != null) {
                if(cur.Next != null) {
                    Point current = cur.Value;
                    Point next = cur.Next.Value;
                    double angle = pointToPointAngle(current, next);
                    double relAngle = angle - prevAngle;
                    if(relAngle < 0) {
                        relAngle += 360;
                    }
                    double distance = pointToPointDistanceFeet(current, next);
                    list.AddLast(new Tuple<double, double>(relAngle, distance));
                    prevAngle = angle;
                }
                cur = cur.Next;
            }
            return list;
        }

        private void form1_Paint(object sender, PaintEventArgs e) {
            this.g = this.CreateGraphics();
            printMap(g, Defines.mapCenter, Defines.mapSize);
        }

        private void mouse_click(object sender, MouseEventArgs e) {
            Point mouseLocation = new Point(e.X, e.Y);
            appendToMoveList(mouseLocation);
            drawRobotPath(g);
        }

        private void button_click(object sender, EventArgs e)
        {
            serialPort1.Open();
            List<int> list = new List<int>();
            bool toCont = true;
            bool recieveData = false;
            int i = 0;
            while(toCont == true)
            {
                try
                {
                    list.Add(serialPort1.ReadChar());
                    recieveData = true;
                    i++;
                    
                }
                catch (System.IO.IOException)
                {
                    toCont = false;
                }
            }
            serialPort1.DiscardInBuffer();
            foreach (int item in list)
            {
                Console.WriteLine(item);
            }
            serialPort1.Close();
            if (recieveData == true)
            {
                //drawPoints();
            }
        }

        private void button2_Click(object sender, EventArgs e) {
            moveList.Clear();
            moveList.AddLast(Defines.mapCenter);
            clearMapArea(g, Defines.mapCenter, Defines.mapSize);
            printMap(g, Defines.mapCenter, Defines.mapSize);
        }
    }
}
