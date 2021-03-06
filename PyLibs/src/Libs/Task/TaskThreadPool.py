﻿# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;
from Libs.DataStruct.MList import MList;
from Libs.Task.TaskThread import TaskThread;
from Libs.Tools.UtilStr import UtilStr;

class TaskThreadPool(GObject):

    def __init__(self):
        super(TaskThreadPool, self).__init__();
        
        self.mTypeId = "TaskThreadPool";


    def initThreadPool(self, numThread, taskQueue):
        self.mList = MList();
        idx = 0;
        while(idx < numThread):
            self.mList.Add(TaskThread(UtilStr.format("TaskThread{0}", idx), taskQueue));
            self.mList[idx].start();
            
            idx = idx + 1;


    def notifyIdleThread(self):
        for item in self.mList.getList():
            if(item.notifySelf()):       # 如果唤醒某个线程就退出，如果一个都没有唤醒，说明当前线程都比较忙，需要等待
                break;


