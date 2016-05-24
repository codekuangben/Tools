﻿#-*- encoding=utf-8 -*-

'''
@brief 一次事件分发，分发一次就清理
'''

from Libs.EventHandle.EventDispatch import EventDispatch

class CallOnceEventDispatch(EventDispatch):
    def __init__(self):
        super(CallOnceEventDispatch, self).__init__();
        
        self.mTypeId = "CallOnceEventDispatch";


    def dispatchEvent(self, dispatchObject):
        super(CallOnceEventDispatch, self).dispatchEvent(dispatchObject);
        self.clearEventHandle();


