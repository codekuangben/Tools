#-*- encoding=utf-8 -*-

import os
import lzma

from FileDirDiff.Core.AppSysBase import AppSysBase
from FileDirDiff.Core.FileListItem import FileListItem

class BuildVersion(object):
    '''
    classdocs
    '''
    def __init__(self):
        '''
        Constructor
        '''
        self.m_curMd5FileHandle = None    # 当前版本的 md5 版本文件
        self.m_curMd5FileCount = 0           # 当前 md5 文件数目
        self.m_curVerFileCount = 0           # 当前 md5 文件数目
        
    def writemd(self, directoryName, filename, md):
        if self.m_curMd5FileHandle is None:
            #with open(config.AppSysBase.instance().m_config.curFilePath(), 'w', encoding='utf-8') as self.m_curMd5FileHandle:
            #    pass
            self.m_curMd5FileHandle = open(AppSysBase.instance().m_config.curMd5FilePath(), 'w', encoding='utf-8')
        
        if self.m_curMd5FileCount > 0:
            self.m_curMd5FileHandle.write('\n')
        self.m_curMd5FileCount += 1
        
        fullpath = os.path.join(directoryName, filename)
        fullpath = fullpath.replace('\\', '/')
        subLen = len(AppSysBase.instance().m_config.m_srcRootPath) + 1
        relPath = fullpath[subLen:]         # 相对文件名字
        with open(fullpath, 'r') as fHandle:
            fHandle.seek(0, 2)
            fileSize = fHandle.tell()
            fHandle.close()

        self.m_curMd5FileHandle.write(relPath + '=' + md + "=" + str(fileSize))
        
        AppSysBase.instance().m_logSys.info('文件  Md5 码:' + fullpath)


    def closemdfile(self):
        if not self.m_curMd5FileHandle is None:
            self.m_curMd5FileHandle.close()
            self.m_curMd5FileHandle = None


    def buildFileMd(self):
        self.m_curMd5FileCount = 0
        AppSysBase.instance().Md5Checker.mdcallback = self.writemd
        AppSysBase.instance().Md5Checker.m_subVersion = AppSysBase.instance().m_config.subVersionByte()
        AppSysBase.instance().Md5Checker.md5_for_dirs(AppSysBase.instance().m_config.m_srcRootPath)
        
        AppSysBase.instance().m_logSys.info(AppSysBase.instance().m_config.m_srcRootPath + 'md5 end')
        
        self.closemdfile()
        
    def buildMiniMd(self):
        # 计算 ModuleApp md5
        fileHandle = open(AppSysBase.instance().m_config.miniMd5FilePath(), 'w', encoding='utf-8')
        md = AppSysBase.instance().Md5Checker.md5_for_file(AppSysBase.instance().m_config.curMd5FilePath())
        
        with open(AppSysBase.instance().m_config.curMd5FilePath(), 'r') as fHandle:
            fHandle.seek(0, 2)
            fileSize = fHandle.tell()
            fHandle.close()
        
        fileHandle.write(AppSysBase.instance().m_config.verFileNameAndExt() + "=" + md + "=" + str(fileSize))

        fileHandle.close()
        AppSysBase.instance().m_logSys.info(AppSysBase.instance().m_config.miniMd5FilePath() + 'md5 end')
        
        
    def lzmaMd5File(self):
        # 压缩
        AppSysBase.instance().m_pParamInfo.m_curInCompressFullFileName = AppSysBase.instance().m_config.curMd5FilePath()
        AppSysBase.instance().m_pParamInfo.m_curOutCompressFullFileName = AppSysBase.instance().m_config.verFilePath()
        #AppSysBase.instance().CmdLine.lzmaCompress()
        
        # 直接拷贝过去， LZMA 压缩还没有实现
        AppSysBase.instance().FileOperate.copyFile(AppSysBase.instance().m_pParamInfo.m_curInCompressFullFileName, AppSysBase.instance().m_pParamInfo.m_curOutCompressFullFileName)
        
        '''
        with open(AppSysBase.instance().m_pParamInfo.m_curInCompressFullFileName, 'r', encoding = 'utf8') as inHandle:
            data = inHandle.read()
            inHandle.close()
            byteArr = bytes(data, encoding = "utf8")
            with lzma.open(AppSysBase.instance().m_pParamInfo.m_curOutCompressFullFileName, 'w') as outHandle:
                outHandle.write(byteArr)
                outHandle.close()
        '''
        
        AppSysBase.instance().m_pParamInfo.m_curInCompressFullFileName = AppSysBase.instance().m_config.miniMd5FilePath()
        AppSysBase.instance().m_pParamInfo.m_curOutCompressFullFileName = AppSysBase.instance().m_config.verMiniPath()
        #AppSysBase.instance().CmdLine.lzmaCompress()
        
        AppSysBase.instance().FileOperate.copyFile(AppSysBase.instance().m_pParamInfo.m_curInCompressFullFileName, AppSysBase.instance().m_pParamInfo.m_curOutCompressFullFileName)
        
        '''
        with open(AppSysBase.instance().m_pParamInfo.m_curInCompressFullFileName, 'r', encoding = 'utf8') as inHandle:
            data = inHandle.read()
            inHandle.close()
            byteArr = bytes(data, encoding = "utf8")
            with lzma.open(AppSysBase.instance().m_pParamInfo.m_curOutCompressFullFileName, 'w') as outHandle:
                outHandle.write(byteArr)
                outHandle.close()
        '''

    def copyFile(self):
        # 拷贝文件
        if AppSysBase.instance().m_bOverVer:
            self.copyFileNoSafe();
        else:
            AppSysBase.instance().m_logSys.info('File is Building, cannot copy file')
            
            
    def copyFileNoSafe(self):
        AppSysBase.instance().FileOperate.copyFile(AppSysBase.instance().m_config.verMiniPath(), AppSysBase.instance().m_config.destVerMiniPath())
        AppSysBase.instance().FileOperate.copyFile(AppSysBase.instance().m_config.verFilePath(), AppSysBase.instance().m_config.destVerFilePath())
            

    def getCurVerFileCount(self):
        return self.m_curVerFileCount
    
    def addCurVerFileCount(self, value):
        self.m_curVerFileCount += value
        
        
    """
            生成清单文件
    """
    def buildFileListManifest(self):
        with open(AppSysBase.instance().m_config.getFile2Unity3dPath(), 'r', encoding = 'utf8') as file2Unity3dPathHandle:
            file2Unity3dPathList = self.parseTextAndRetList(file2Unity3dPathHandle);
            file2Unity3dPathHandle.close()
            
        with open(AppSysBase.instance().m_config.getFile2DirPath(), 'r', encoding = 'utf8') as file2DirPathHandle:
            file2DirPathList = self.parseTextAndRetList(file2DirPathHandle);
            file2DirPathHandle.close()

        with open(AppSysBase.instance().m_config.getFileListPath(), 'w', encoding = 'utf8') as fileListHandle:
            bFirstLine = True
#             for (key, value) in file2Unity3dPathList.items():
#                 if value in file2DirPathList:
#                     if bFirstLine:
#                         bFirstLine = False
#                     else:
#                         fileListHandle.write('\n')
#                     fileListHandle.write("{0}={1}={2}".format(key, value, file2DirPathList[value]))
#                 else:
#                     AppSysBase.instance().m_logSys.info("{0} canot find".format(key));
            for item in file2Unity3dPathList:
                idx = self.findElemIdx(item.m_sndName, file2DirPathList)
                if idx != -1:
                    if bFirstLine:
                        bFirstLine = False
                    else:
                        fileListHandle.write('\n')
                    fileListHandle.write("{0}={1}={2}".format(item.m_firstName, item.m_sndName, file2DirPathList[idx].m_sndName))
                else:
                    AppSysBase.instance().m_logSys.info("{0} canot find".format(item.m_firstName));
            
            
                    
        fileListHandle.close()
                 

    def parseTextAndRetDic(self, fileHandle):
        cont = fileHandle.read()
        strlist = cont.split('\n')
        idx = 0
        substrList = []
        retMap = {}
        listlen = len(strlist)
        while(idx < listlen):
            substrList = strlist[idx].split('=')
            if len(substrList[0]):
                retMap[substrList[0]] = substrList[1]
            idx += 1

        return retMap
    
    
    def parseTextAndRetList(self, fileHandle):
        cont = fileHandle.read()
        strlist = cont.split('\n')
        idx = 0
        substrList = []
        retList = []
        listlen = len(strlist)
        while(idx < listlen):
            substrList = strlist[idx].split('=')
            if len(substrList[0]):
                item = FileListItem()
                item.m_firstName = substrList[0]
                item.m_sndName = substrList[1]
                retList.append(item)
            idx += 1

        return retList


    def findElemIdx(self, elem, elemList):
        idx = 0
        for item in elemList:
            if item.m_firstName == elem:
                return idx;
            
            idx += 1;
                
        return -1


