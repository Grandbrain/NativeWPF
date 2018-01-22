using System;
using System.Windows.Forms;
using lib;

namespace app
{
    public partial class MainWindow
    {
        private Scene _scene;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void ControlHandleCreated(object sender, EventArgs e)
        {
            var control = sender as Control;
            if (control != null) _scene = new Scene(control.Handle, control.Width, control.Height);
        }

        private void ControlResize(object sender, EventArgs e)
        {
            var control = sender as Control;
            if (control != null) _scene?.Resize(control.Width, control.Height);
        }

        private void ControlPaint(object sender, PaintEventArgs e)
        {
            _scene?.Draw();
        }
    }
}
