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
        List<int> arr = new List<int>();
        double angle;
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

        private void print_points(Point center)
        {
            //angle = 360 / numPoints;

        }

        private void form1_Paint(object sender, PaintEventArgs e) {
            this.g = this.CreateGraphics();
            Point topLeft = new Point(Defines.MAP_X, Defines.MAP_Y);
            Point mapCenter = new Point(topLeft.X + Defines.MAP_SIZE / 2, topLeft.Y + Defines.MAP_SIZE / 2);
            Size mapSize = new Size(Defines.MAP_SIZE, Defines.MAP_SIZE);
            g.DrawRectangle(Pens.Black, generateCenterPointRectangle(mapCenter, mapSize));
            g.FillRectangle(Brushes.Red, generateCenterPointRectangle(mapCenter, new Size(Defines.ROBOT_SIZE, Defines.ROBOT_SIZE)));
            printMap(g, mapCenter, mapSize);
            // this.Cursor = new Cursor(Cursor.Current.Handle);
            //Cursor.Position = new Point(Cursor.Position.X - 50, Cursor.Position.Y - 50);
            //while (true) {
            //    g.DrawRectangle(Pens.Black, generateCenterPointRectangle(Cursor.Position, new Size(3, 3)));
            //}
        }

        private void mouse_click(object sender, MouseEventArgs e)
        {
            this.g.DrawRectangle(Pens.Black, generateCenterPointRectangle(new Point(e.X,e.Y), new Size(3,3)));
        }

        private void button_click(object sender, EventArgs e)
        {

            //Console.WriteLine(arr);
            serialPort1.Open();
            bool toCont = true;
            bool recieveData = false;
            arr.Clear();
            int i = 0;


            while (toCont == true)
            {
                System.Threading.Thread.Sleep(100);
                try
                {
                    Console.WriteLine("YAHHHHHH");
                    char c = (char)serialPort1.ReadChar();
                    if (c == 's')
                    {
                        while (toCont == true)
                        {
                            System.Threading.Thread.Sleep(100);
                            try
                            {
                                Console.WriteLine("YAHHHHHH");
                                Console.WriteLine(i);
                                arr.Add(serialPort1.ReadChar());
                                Console.WriteLine("Data: {0}", arr[i]);
                                recieveData = true;
                                i++;

                            }
                            catch (System.IO.IOException)
                            {
                                toCont = false;
                            }
                        }
                    }
                }
                catch (System.IO.IOException)
                {
                }
            }
            
            serialPort1.DiscardInBuffer();
            Console.WriteLine("HERE");
            foreach (int item in arr)
            {
                Console.WriteLine(item);
            }
            serialPort1.Close();
            if (recieveData == true)
            {
                //drawPoints();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            System.Threading.Thread.Sleep(3000);
            serialPort1.Open();
            //serialPort1.WriteLine("s");
            System.Threading.Thread.Sleep(100);
            serialPort1.Write(new char[] { 's' }, 0, 1);
            int numToSend = 20;
            serialPort1.Write(new char[] { (char)numToSend }, 0, 1);
            System.Threading.Thread.Sleep(100);
            for (int i = 2; i < 6; i++)
            {
                Console.WriteLine("Yahhhh {0}", );
                serialPort1.Write(new char[] { (char)(i*2) }, 0, 1);
                System.Threading.Thread.Sleep(100);
            }
            serialPort1.Close();
        }
    }
}
