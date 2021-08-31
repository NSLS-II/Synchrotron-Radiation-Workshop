#############################################################################
# Basic Input/Output Utility Functions
# v 0.02
#############################################################################

from copy import *

#**********************Auxiliary function to write auxiliary/debugging information to an ASCII file:
def write_text(_text, _file_path):
    f = open(_file_path, 'w')
    f.write(_text + '\n')
    f.close()

#**********************Auxiliary function to read-in data comumns from ASCII file (2D table):
def read_ascii_data_cols(_file_path, _str_sep, _i_col_start=0, _i_col_end=-1, _n_line_skip=0, _float=True, _n_line_skip_end=0): #OC20042020
#def read_ascii_data_cols(_file_path, _str_sep, _i_col_start=0, _i_col_end=-1, _n_line_skip=0, _float=True): #OC24112019
#def read_ascii_data_cols(_file_path, _str_sep, _i_col_start=0, _i_col_end=-1, _n_line_skip=0):
    """
    Auxiliary function to read-in data comumns from ASCII file (2D table)
    :param _file_path: full path (including file name) to the file
    :param _str_sep: column separation symbol(s) (string)
    :param _i_col_start: initial data column to read
    :param _i_col_end: final data column to read
    :param _n_line_skip: number of lines to skip in the beginning of the file
    :return: 2D list containing data columns read
    """
    f = open(_file_path, 'r')
    lines = f.readlines()

    resCols = []

    #nCol = _i_col_end - _i_col_start + 1
    #for iCol in range(nCol):
    #    resCols.append([])

    nRows = len(lines) - _n_line_skip - _n_line_skip_end #OC20042020
    #nRows = len(lines) - _n_line_skip

    for i in range(nRows):
        curLine = lines[_n_line_skip + i]
        curLineParts = curLine.split(_str_sep)
        curNumParts = len(curLineParts)
        #print(curLineParts)

        colCount = 0; colCountTrue = 0
        for iCol in range(curNumParts):
            curPart = curLineParts[iCol]
            #print(curPart)
            
            if(len(curPart) > 0):
                if(((_i_col_start <= colCount) or (_i_col_start < 0)) and ((colCount <= _i_col_end) or (_i_col_end < 0))):
                    if len(resCols) < (colCountTrue + 1): resCols.append([])
                    #resCols[colCountTrue].append(float(curPart))
                    if(_float): resCols[colCountTrue].append(float(curPart)) #OC24112019
                    else: resCols[colCountTrue].append(curPart)
                    colCountTrue += 1
                colCount += 1
    f.close()
    return resCols #attn: returns lists, not arrays!

#**********************Auxiliary function to read-in data rows from ASCII file (2D table):
def read_ascii_data_rows(_file_path, _str_sep, _i_col_start=0, _i_col_end=-1, _i_row_start=0, _i_row_end=-1, _try_float=True): #OC28012021
    """
    Auxiliary function to read-in data rows from ASCII file (2D table)
    :param _file_path: full path (including file name) to the file
    :param _str_sep: column separation symbol(s) (string)
    :param _i_col_start: initial data column to read
    :param _i_col_end: final data column to read
    :param _i_row_start: initial data row to read
    :param _i_row_end: final data row to read
    :param _try_float: attempt to convert input characters to float or not
    :return: 2D list containing data rows read
    """
    f = open(_file_path, 'r')
    lines = f.readlines()
    f.close()

    i_row_start = 0 if(_i_row_start < 0) else _i_row_start
    i_row_end_p_1 = len(lines)
    if((_i_row_end > 0) and (_i_row_end < i_row_end_p_1)): i_row_end_p_1 = _i_row_end + 1

    i_col_start = 0 if(_i_col_start < 0) else _i_col_start
    i_col_end_p_1 = _i_col_end + 1

    resRows = []    
    for i in range(i_row_start, i_row_end_p_1):
        curLine = lines[i]
        curLineParts = curLine.split(_str_sep)
        curNumParts = len(curLineParts)
        #print(curLineParts)

        i_col_end_p_1 = curNumParts if(_i_col_end < 0 or _i_col_end >= curNumParts) else i_col_end_p_1

        curRow = []
        for iCol in range(i_col_start, i_col_end_p_1):
            curPart = curLineParts[iCol]
            #print(curPart)
            
            if(_try_float):
                try: curPart = float(curPart)
                except: pass
            curRow.append(curPart)

        resRows.append(curRow)
    
    return resRows #attn: returns lists, not arrays!

#**********************Auxiliary function to write (save) data comumns to ASCII file (2D table):
def write_ascii_data_cols(_file_path, _cols, _str_sep, _str_head=None, _i_col_start=0, _i_col_end=-1):
    """
    Auxiliary function to write tabulated data (columns, i.e 2D table) to ASCII file
    :param _file_path: full path (including file name) to the file to be (over-)written
    :param _cols: array of data columns to be saved to file
    :param _str_sep: column separation symbol(s) (string)
    :param _str_head: header (string) to write before data columns
    :param _i_col_start: initial data column to write
    :param _i_col_end: final data column to write
    """
    f = open(_file_path, 'w')

    if(_str_head != None):
        lenStrHead = len(_str_head)
        if(lenStrHead > 0):
            strHead = _str_head
            if(_str_head[lenStrHead - 1] != '\n'):
                strHead = copy(_str_head) + '\n'
            f.write(strHead)
    if(_cols == None):
        f.close(); return
        
    nCols = len(_cols)
    if(nCols <= 0):
        f.close(); return

    nLines = len(_cols[0])
    for i in range(1, nCols):
        newLen = len(_cols[i])
        if(nLines < newLen): nLines = newLen

    strSep = '\t'
    if(_str_sep != None):
        if(len(_str_sep) > 0): strSep = _str_sep

    strTot = ''
    iColEndP1 = nCols
    if((_i_col_end >= 0) and (_i_col_end < nCols)): iColEndP1 = _i_col_end + 1
    iColEnd = iColEndP1 - 1
    nLinesM1 = nLines - 1
        
    for i in range(nLines):
        curLine = ''
        for j in range(_i_col_start, iColEndP1):
            curElem = ' '
            if(i < len(_cols[j])): curElem = repr(_cols[j][i])
            curLine += curElem
            if(j < iColEnd): curLine += strSep
        if(i < nLinesM1): curLine += '\n'
        strTot += curLine
        
    f.write(strTot)
    f.close()

#**********************Auxiliary function to write (save) data rows to ASCII file (2D table):
def write_ascii_data_rows(_file_path, _rows, _str_sep, _str_head=None, _i_col_start=0, _i_col_end=-1, _i_row_start=0, _i_row_end=-1): #OC16112019
    """
    Auxiliary function to write tabulated data (columns, i.e 2D table) to ASCII file
    :param _file_path: full path (including file name) to the file to be (over-)written
    :param _rows: array of data rows (/lines) to be saved to file
    :param _str_sep: column separation symbol(s) (string)
    :param _str_head: header (string) to write before data columns
    :param _i_col_start: initial data column to write
    :param _i_col_end: final data column to write
    :param _i_row_start: initial data row to write
    :param _i_row_end: final data row to write
    """
    f = open(_file_path, 'w')

    if(_str_head != None):
        lenStrHead = len(_str_head)
        if(lenStrHead > 0):
            strHead = _str_head
            if(_str_head[lenStrHead - 1] != '\n'):
                strHead = copy(_str_head) + '\n'
            f.write(strHead)
    if(_rows == None):
        f.close(); return
        
    nRows = len(_rows)
    nCols = len(_rows[0])

    if((nRows <= 0) or (nCols <= 0)):
        f.close(); return

    strSep = '\t'
    if(_str_sep != None):
        if(len(_str_sep) > 0): strSep = _str_sep

    strTot = ''
    iColEndP1 = nCols
    if((_i_col_end >= 0) and (_i_col_end < nCols)): iColEndP1 = _i_col_end + 1

    iRowEndP1 = nRows
    if((_i_row_end >= 0) and (_i_row_end < nRows)): iRowEndP1 = _i_row_end + 1

    iColEnd = iColEndP1 - 1
    iRowEnd = iRowEndP1 - 1
        
    for i in range(_i_row_start, iRowEndP1):
        curLine = ''
        curDataRow = _rows[i]
        for j in range(_i_col_start, iColEndP1):
            curElem = repr(curDataRow[j])
            curLine += curElem
            if(j < iColEnd): curLine += strSep
        if(i < iRowEnd): curLine += '\n'
        strTot += curLine
        
    f.write(strTot)
    f.close()

#********************** Read data from an image file:
def read_image(image_path, _do8bit=True):  #OC23102019
#def read_image(image_path):  # MR26102017
    """Read data from an image file.

    :param image_path: full path to the image.
    :return: dict with the processed data.
    """

    msg = '{0} library is not installed. Use "pip install {0}" to install it.'
    try:
        import numpy as np
    except:
        raise ImportError(msg.format('numpy'))
    try:
        from PIL import Image
    except:
        raise ImportError(msg.format('pillow'))

    #OC11112018 (as suggested by Rafael Celestre, to walk around image size limit)
    Image.MAX_IMAGE_PIXELS = None

    # Read the image:
    raw_image = Image.open(image_path)
    image_format = raw_image.format

    #OC23102019
    #raw_image = raw_image.convert('L')
    if(_do8bit): raw_image = raw_image.convert('L')

    # Convert it to NumPy array:
    data = np.array(raw_image)
    if image_format not in ('TIFF', 'PNG', 'BMP', 'GIF', 'JPEG'):
        raise ValueError('"{}" format is not supported at the moment.'.format(raw_image.format))

    # Get bits per point:
    mode_to_bpp = {'1': 1, 'L': 8, 'P': 8, 'I;16': 16, 'RGB': 24, 'RGBA': 32, 'CMYK': 32, 'YCbCr': 24, 'I': 32, 'F': 32}
    bpp = mode_to_bpp[raw_image.mode]
    limit_value = float(2 ** bpp - 1)

    return {
        'data': data,
        'raw_image': raw_image,
        'limit_value': limit_value,
    }
