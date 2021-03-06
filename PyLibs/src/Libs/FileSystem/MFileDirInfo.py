# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;
from Libs.DataStruct.MList import MList;

class MFileInfo(GObject):
    def __init__(self):
        super(MFileInfo, self).__init__();
        
        self.mTypeId = "MFileInfo";
        
        self.mFullPath = "";
        self.mFileName = "";
        self.mLength = 0;
        
        
class MDirInfo(GObject):
    def __init__(self):
        super(MDirInfo, self).__init__();
        
        self.mTypeId = "MDirInfo";
        
        self.mFullPath = "";
        self.mDirName = "";
        self.mLength = 0;
        

class MFileAndDirList(GObject):
    
    def __init__(self):
        super(MFileAndDirList, self).__init__();
        
        self.mTypeId = "MFileAndDirList";
        
        self.mFileList = MList();
        self.mDirList = MList();

    
