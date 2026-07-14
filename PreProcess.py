import os
import pathlib
import sys
import re

result = ""
if_stack = [] # 末端にFalseがあれば無視、Trueなら有効
defined_symbol = set()

def extract_source(filepath:str, curdir:str):
    global result
    global if_stack
    global defined_symbol

    fullpath = pathlib.Path(curdir, filepath)

    with open(fullpath, "r", encoding="utf_8_sig") as srcfile:
        src_contents = srcfile.readlines()
        
        INCLUDE_RE = r'^#include "(?P<include_path>[^\s]+)".*'
        DEFINE_RE = r'^#define[\s]+(?P<define_name>[^\s]+).*'
        IFNDEF_RE = r'^#ifndef[\s]+(?P<define_name>[^\s]+).*'
        IFDEF_RE = r'^#ifdef[\s]+(?P<define_name>[^\s]+).*'
        ENDIF_RE = r'^#endif.*'

        for l in src_contents:
            # ifndefにより無視される領域は全てのifndefとifdefを無視判定とする
            # endifが来たら無視判定を取り下げていく
            if len(if_stack) != 0 and not if_stack[-1]:
                if(re.match(ENDIF_RE, l)):
                    result += l
                    if_stack.pop()
                elif(re.match(IFNDEF_RE, l)):
                    result += l
                    if_stack.append(False)
                elif(re.match(IFDEF_RE, l)):
                    result += l
                    if_stack.append(False)
            
            else :
                # includeを処理する
                # ファイルの中身をそのまま展開する
                if(re.match(INCLUDE_RE, l)):
                    re_result = re.search(INCLUDE_RE, l)
                    include_path = re_result.group("include_path")
                    dirname = os.path.dirname(os.path.abspath(filepath))
                    extract_source(include_path, dirname)

                # defineを処理する
                # 定義された定数をsetに突っ込んでifndefの判定に利用する
                elif(re.match(DEFINE_RE, l)):
                    re_result = re.search(DEFINE_RE, l)
                    define_name = re_result.group("define_name")
                    defined_symbol.add(define_name)

                    result += l
                # ifndefを処理する
                # すでにdefineされていたら無視判定を入れる
                elif(re.match(IFNDEF_RE, l)):
                    re_result = re.search(IFNDEF_RE, l)
                    define_name = re_result.group("define_name")
                    if(define_name in defined_symbol):
                        if_stack.append(False)
                    else:
                        if_stack.append(True)

                    result += l
                # ifdefを処理する
                # すでにdefineされていたら無視判定を入れる
                elif(re.match(IFDEF_RE, l)):
                    re_result = re.search(IFDEF_RE, l)
                    define_name = re_result.group("define_name")
                    if(define_name not in defined_symbol):
                        if_stack.append(False)
                    else:
                        if_stack.append(True)

                    result += l
                # endifを処理する
                # 無視判定を取り下げるだけ
                elif(re.match(ENDIF_RE, l)):
                    result += l

                    if_stack.pop()
                else:
                    result += l

        result += '\n'
    return

if __name__ == "__main__":
    cwd_path = os.getcwd()

    OUT_DIR = "submit"
    dir_path = pathlib.Path(cwd_path, OUT_DIR)

    # 提出用フォルダ作成
    if not os.path.isdir(dir_path):
        os.mkdir(path = dir_path)

    src_filename = sys.argv[1]
    
    extract_source(src_filename, cwd_path)
    out_name = os.path.basename(src_filename)

    with open(pathlib.Path(dir_path, out_name), "w", encoding="utf_8_sig") as out_file:
        out_file.write(result)