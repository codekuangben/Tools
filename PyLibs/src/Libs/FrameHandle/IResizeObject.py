# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;

class IResizeObject(GObject):
    
    def __init__(self):
        super(IResizeObject, self).__init__();
        
        self.mTypeId = "IResizeObject";
        
        
    def onResize(self, viewWidth, viewHeight):
        pass;

