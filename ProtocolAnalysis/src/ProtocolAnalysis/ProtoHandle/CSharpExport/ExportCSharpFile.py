#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.ProtoHandle.ProtoParse.ProtoFileBase import eFileType
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoElemBase import eProtoElemType
from ProtocolAnalysis.ProtoHandle.CSharpExport.CSharpKeyWord import CSharpKeyWord


class ExportCSharpFile():
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
    
    
    def export(self):
        for file in AppSysBase.instance().getConfigPtr().getProtoFilesList().getFilesListPtr():
            if file.getFileType() == eFileType.eFile:       # 如果是文件，直接解析
                fileNameNoExt = file.getFileNameNoExt()
                fileOutPath = AppSysBase.instance().getConfigPtr().getCSOutPath();
                fullPath = "{0}/{1}.cs".format(fileOutPath, fileNameNoExt)
                with open(fullPath, 'w', encoding = 'utf8') as fHandle:
                    for protoElem in file.getProtoElemList():   # 遍历整个文件列表
                        if protoElem.getType() == eProtoElemType.eMessage:  # 如果是消息
                            self.exportMessage(fHandle, protoElem)
                    
                    fHandle.close()         # 关闭文件输入
                        
    
    # 导出命名空间
    def exportNSStart(self, fHandle):
        startNS = "namespace SDK.Lib"
        fHandle.write(startNS)
        
        startNS = "{"
        fHandle.write(startNS)
    
    
    # 导出命名空间结束
    def exportNSEnd(self, fHandle):
        endNS = "}"
        fHandle.write(endNS)
        
        
    
    
    # 导出一个 ProtoMessage 
    def exportMessage(self, fHandle, message):
        # 写入类的名字
        clsName = "public class {0}\n".format(message.getTypeName())
        fHandle.write(clsName)
        # 输入左括号
        leftBrace = "{0}\n".format("{")
        fHandle.write(leftBrace)
        
        # 写入类的成员
        for member in message.getMemberList():
            memberStr = "\tpublic {0} {1};\n".format(CSharpKeyWord.sProtoKey2CSharpKey[member.getTypeName()], member.getVarName())
            fHandle.write(memberStr)
            
        # 写入一个空行
        spaceLine = "\n"
        fHandle.write(spaceLine)
        
        # 写入构造函数
        constructFuncStr = "\tpublic {0}()\n".format(message.getTypeName())
        fHandle.write(constructFuncStr)
        
        constructFuncStr = "\t{0}\n".format("{")
        fHandle.write(constructFuncStr)
        
        constructFuncStr = "\t{0}\n".format("}")
        fHandle.write(constructFuncStr)
        
        # 写入一个空行
        spaceLine = "\n"
        fHandle.write(spaceLine)
        
        # 写入序列化函数    
        serializeStr = "\toverride public void serialize(ByteBuffer ba)\n"
        fHandle.write(serializeStr)
        
        serializeStr = "\t{0}\n".format("{")
        fHandle.write(serializeStr)
        
        serializeStr = "\t{0}\n".format("}")
        fHandle.write(serializeStr)
        
        serializeStr = "{0}\n".format("}")
        fHandle.write(serializeStr)
        # 吸入反序列化函数

