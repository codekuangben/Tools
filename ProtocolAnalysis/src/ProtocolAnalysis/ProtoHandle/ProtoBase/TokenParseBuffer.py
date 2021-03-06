#-*- encoding=utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoKeyWord import ProtoKeyWordList


class TokenParseBuffer(object):
    '''
    classdocs
    '''
    # 目前分隔符只有空格、换行、水平制表符，如果需要可以加入其它的分隔符，例如分号 ";" 之类的
    m_sSplitToken = [" ", "\n", "\t"]


    def __init__(self):
        '''
        Constructor
        '''
        self.m_fileBytes = ""       # 整个 Proto 的内容
        self.m_curPos = 0           # 当前读写位置
        
    def openFile(self, fileName):
        with open(fileName, 'r', encoding = 'utf8') as fHandle:
            self.m_fileBytes = fHandle.read()
            self.m_curPos = 0


    def isEOF(self):
        return self.m_curPos == len(self.m_fileBytes)
    
    
    # 从字符串的左边获取一个符号，并且删除这个符号
    def getTokenAndRemove(self):
        self.skipSpaceBrTab()
        
        idx = self.m_curPos;
        ret = ''
        
        while idx < len(self.m_fileBytes):
            if self.isSpaceBrTab(self.m_fileBytes[idx]):    # 空格、换行、tab 键还是保留在原始缓冲区中的
                break 
            ret += self.m_fileBytes[idx]
            idx += 1
            
        #if len(ret):
        #    self.m_fileBytes = self.m_fileBytes[idx:]         # 删除内容
        self.m_curPos = idx
            
        #self.skipSpaceBrTab()
        
        return ret


    # 获取一个符号，但是不从缓冲区中移除符号
    def getTokenAndNoRemove(self):
        self.skipSpaceBrTab()
        
        idx = self.m_curPos;
        ret = ''
        
        while idx < len(self.m_fileBytes):
            if self.isSpaceBrTab(self.m_fileBytes[idx]):    # 空格、换行、tab 键还是保留在原始缓冲区中的
                break 
            ret += self.m_fileBytes[idx]
            idx += 1
            
        #self.skipSpaceBrTab()
        
        return ret
        

    # 移除一个符号，并且返回符号长度
    def removeOneToken(self):
        self.skipSpaceBrTab()
        
        idx = self.m_curPos;
        ret = ''
        
        while idx < len(self.m_fileBytes):
            if self.isSpaceBrTab(self.m_fileBytes[idx]):    # 空格、换行、tab 键还是保留在原始缓冲区中的
                break
            ret += self.m_fileBytes[idx]
            idx += 1
            
        #if len(ret):
        #    self.m_fileBytes = self.m_fileBytes[idx:]         # 删除内容
        
        self.m_curPos = idx
            
        #self.skipSpaceBrTab()
        
        return len(ret) 


    # 跳过当前行
    def skipCurLine(self):
        idx = self.m_curPos;
        ret = ''
        
        while idx < len(self.m_fileBytes):
            if self.m_fileBytes[idx] == '\n':       # 空格、换行、tab 键还是保留在原始缓冲区中的
                break;
            ret += self.m_fileBytes[idx]
            idx += 1

        self.m_curPos = idx


    # 是否是空格、换行、或者 Tab 键
    def isSpaceBrTab(self, char):
        if char == ' ' or char == '\n' or char == '\t':       # 如果遇到空格或者换行符，就算是一个符号
            return True
        
        return False

    # 跳过空格和换行
    def skipSpaceBrTab(self):
        idx = self.m_curPos;
        ret = ''
        
        while idx < len(self.m_fileBytes):
            if not self.isSpaceBrTab(self.m_fileBytes[idx]):
                break
            ret += self.m_fileBytes[idx]
            idx += 1

        self.m_curPos = idx

    
    def skipSpace(self):
        idx = self.m_curPos;
        ret = ''
        
        while idx < len(self.m_fileBytes):
            if self.m_fileBytes[idx] != ' ':
                break
            ret += self.m_fileBytes[idx]
            idx += 1
            
        self.m_curPos = idx
    
    
    def skipBr(self):
        idx = self.m_curPos;
        ret = ''
        
        while idx < len(self.m_fileBytes):
            if self.m_fileBytes[idx] != '\n':
                break;
            ret += self.m_fileBytes[idx]
            idx += 1
            
        self.m_curPos = idx        
    
    
    def skipTab(self):
        idx = self.m_curPos;
        ret = ''
        
        while idx < len(self.m_fileBytes):
            if self.m_fileBytes[idx] != '\t':
                break;
            ret += self.m_fileBytes[idx]
            idx += 1
            
        self.m_curPos = idx
        
        
    def getLineNoRemove(self):
        curPos_ = self.m_curPos             # 保存当前位置信息
        
        self.skipSpaceBrTab()               # 一行的开始必定是 "\n"，因此跳过
        
        idx = self.m_curPos
        ret = ""
        
        while idx < len(self.m_fileBytes):
            if self.m_fileBytes[idx] == '\n':
                break;
            ret += self.m_fileBytes[idx]            # 将 "\n" 不放到当前行中
            idx += 1
        
        self.m_curPos = curPos_
        
        return ret


    def getLineRemove(self):
        self.skipSpaceBrTab()                       # 一行的开始必定是 "\n"，因此跳过
        
        idx = self.m_curPos
        ret = ""
        
        while idx < len(self.m_fileBytes):
            if self.m_fileBytes[idx] == '\n':
                break;
            ret += self.m_fileBytes[idx]            # 将 "\n" 不放到当前行中
            idx += 1
        
        self.m_curPos = idx
        
        return ret


    # 获取单行注释和多行注释和空行
    def getCommentAndSpaceLine(self):
        self.skipSpaceBrTab()                       # 一行的开始必定是 "\n"，因此跳过
        
        ret = ""
        minIdx = len(self.m_fileBytes)
        curIdx = 0
        
        #curIdx = self.m_fileBytes.find(ProtoKeyWord.eMessage, self.m_curPos)     # "message" 关键字查找
        #if curIdx >= 0 and minIdx > curIdx:
        #    minIdx = curIdx
            
        #curIdx = self.m_fileBytes.find(ProtoKeyWord.eEnum, self.m_curPos)     # "enum" 关键字查找
        #if curIdx >= 0 and minIdx > curIdx:
        #    minIdx = curIdx
            
        #curIdx = self.m_fileBytes.find(ProtoKeyWord.ePackage, self.m_curPos)     # "package" 关键字查找
        #if curIdx >= 0 and minIdx > curIdx:
        #    minIdx = curIdx
            
        #curIdx = self.m_fileBytes.find(ProtoKeyWord.eHeader, self.m_curPos)     # "header" 关键字查找
        #if curIdx >= 0 and minIdx > curIdx:
        #    minIdx = curIdx
            
        #curIdx = self.m_fileBytes.find(ProtoKeyWord.eImport, self.m_curPos)     # "import" 关键字查找
        #if curIdx >= 0 and minIdx > curIdx:
        #    minIdx = curIdx
        
        for delimiter in ProtoKeyWordList.sKeyWordDelimiter:
            curIdx = self.m_fileBytes.find(delimiter, self.m_curPos)     # 关键字查找
            if curIdx >= 0 and minIdx > curIdx:
                minIdx = curIdx
        
        if minIdx < len(self.m_fileBytes):      # 如果可以找到关键字
            ret = self.m_fileBytes[self.m_curPos : minIdx]
            self.m_curPos = minIdx
        else:       # 如果没有找到关键字，就说明已经到文件的结尾都没有这些关键字了，全部作为注释了
            ret = self.m_fileBytes[self.m_curPos : ]
            self.m_curPos = len(self.m_fileBytes)
            
        if len(ret) > 0:    # 如果有注释
            if minIdx < len(self.m_fileBytes):      # 如果是最后的注释，全部取出来，否则需要将注释最后面的 \t ' ' \n 删除
                # 删除最后一个 "\n"
                #lastNextIdx = ret.rfind("\n")
                #if lastNextIdx != -1:
                #    ret = ret[:lastNextIdx]
                #strlist = ret.split('\n')
                ret = self.delTailSplitToken(ret)
            
        strlist = ret.split('\n')
        
        #return ret
        return strlist
    
    
    def delTailSplitToken(self, tailStr):
        if len(tailStr) > 0:
            for idx in range(len(tailStr) - 1, -1, -1):
                if idx >= 0:
                    if not tailStr[idx] in TokenParseBuffer.m_sSplitToken:
                        break;
            
            if idx >= 0:
                return tailStr[0 : idx + 1]
        
        return ""
    
