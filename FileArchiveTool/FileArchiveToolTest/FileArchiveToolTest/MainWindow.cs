﻿using System;
using Gtk;

namespace FileArchiveToolTest
{
	public partial class MainWindow: Gtk.Window
	{
		public MainWindow () : base (Gtk.WindowType.Toplevel)
		{
			Build ();

			ArchiveData pArchiveData = new ArchiveData ();
			UnArchiveParam pUnArchiveParam = new UnArchiveParam ();
			string path = "E:\\aaaaa\\新建文件夹_0.abc";
			pUnArchiveParam.setUnArchiveFilePath (path);
			pUnArchiveParam.setUnArchiveOutDir (Util.getFullPathNoExtName (path));
			pArchiveData.unArchiveFile (pUnArchiveParam);
		}

		protected void OnDeleteEvent (object sender, DeleteEventArgs a)
		{
			Application.Quit ();
			a.RetVal = true;
		}
	}
}