﻿/*  This is RTF to HTML converter, implemented as a text filter, generally.
    Copyright (C) 2003 Valentin Lavrinenko, vlavrinenko@users.sourceforge.net

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


/*  ??? ????????? RTF ? HTML, ?????????????, ? ????????, ??? ????????? ??????.
    Copyright (C) 2003 ???????? ??????????, vlavrinenko@users.sourceforge.net

    ?????? ?????????? ???????? ????????? ??????????? ????????????. ??
    ?????? ?????????????? ?? ?/??? ?????????????? ? ???????????? ? ?????????
    ?????? 2.1 ???? ?? ?????? ?????? ? ????????? ????? ??????? ??????
    ??????????? ???????????? ???????? ????????????? ?????????? GNU,
    ?????????????? Free Software Foundation.

    ?? ?????????????? ??? ?????????? ? ??????? ?? ??, ??? ??? ????? ???
    ????????, ?????? ?? ????????????? ?? ??? ??????? ????????, ? ??? ?????
    ???????? ????????? ????????? ??? ??????? ? ??????????? ??? ?????????????
    ? ?????????? ?????. ??? ????????? ????? ????????? ?????????? ????????????
    ?? ??????????? ???????????? ????????? ????????????? ?????????? GNU.

    ?????? ? ?????? ??????????? ?? ?????? ???? ???????? ????????? ???????????
    ???????????? ???????? ????????????? ?????????? GNU. ???? ?? ??? ??
    ????????, ???????? ?? ???? ?? Free Software Foundation, Inc., 59 Temple
    Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#include "config.h"
#include "rtf_table.h"
#include "rtf_tools.h"
#include "rtf_keyword.h"
#include "fmt_opts.h"
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <string>
#include "share/WizQtHelper.h"
#include "share/WizMisc.h"


int GetTabSize()
{
    static int nTabSize = 4;
    //
//    if (nTabSize > 0)
//        return nTabSize;
//    //
//    CString strFileName = WizGetAppPath() + _T("wizrtf2html.ini");
//    //
//    nTabSize = GetPrivateProfileInt(_T("Rtf2Html"), _T("TabSize"), 4, strFileName);
    //
    return nTabSize;
}




//int rtf2html(const char *rtfText, std::string& strResult)
//{
//    try
//    {
//        std::string str_in(rtfText);

//        std::string::iterator buf_in=str_in.begin(), buf_in_end=str_in.end();
//        colorvect colortbl;
//        fontmap fonttbl;
//        std::string title;

//        bool bAsterisk=false;
//        fo_stack foStack;
//        formatting_options cur_options;
//        std::string html;
//        html_text par_html(cur_options);

//        /* CellDefs in rtf are really queer. We'll keep a list of them in main()
//      and will give an iterator into this list to a row */
//        table_cell_defs_list CellDefsList;
//        table_cell_defs_list::iterator CurCellDefs;
//        table_cell_def *tcdCurCellDef=new table_cell_def;
//        table_cell *tcCurCell=new table_cell;
//        table_row *trCurRow=new table_row;
//        table *tblCurTable=new table;
//        int iLastRowLeft=0, iLastRowHeight=0;
//        std::string t_str;

//        bool bInTable=false;
//        int iDocWidth=12240;
//        int iMarginLeft=1800;
//        while(buf_in!=buf_in_end)
//        {
//            switch (*buf_in)
//            {
//            case '\\':
//            {
//                rtf_keyword kw(++buf_in);
//                if (kw.is_control_char())
//                {
//                    switch (kw.control_char())
//                    {
//                    case '\\': case '{': case '}':
//                        par_html.write(kw.control_char());
//                        break;
//                    case '\'':
//                        par_html.write(char_by_code(buf_in));
//                        break;
//                    case '*':
//                        bAsterisk=true;
//                        break;
//                    case '~':
//                        par_html.write("&nbsp;");
//                        break;
//                    }
//                }
//                else //kw.is_control_char
//                {
//                    if (bAsterisk)
//                    {
//                        bAsterisk=false;
//                        skip_group(buf_in);
//                        cur_options=foStack.top();
//                        foStack.pop();
//                    }
//                    else
//                    {
//                        switch (kw.keyword())
//                        {
//                        case rtf_keyword::rkw_filetbl:
//                        case rtf_keyword::rkw_stylesheet:
//                        case rtf_keyword::rkw_header:
//                        case rtf_keyword::rkw_footer: case rtf_keyword::rkw_headerf:
//                        case rtf_keyword::rkw_footerf: case rtf_keyword::rkw_pict:
//                        case rtf_keyword::rkw_object:
//                            // we'll skip such groups
//                            skip_group(buf_in);
//                            break;
//                            // document title
//                        case rtf_keyword::rkw_info:
//                        {
//                            int depth=1;
//                            bool in_title=false;
//                            while (depth>0)
//                            {
//                                //                     std::cout<<std::string(buf_in).substr(0,20)<<"\t"<<depth<<std::endl;
//                                switch (*buf_in)
//                                {
//                                case '\\':
//                                {
//                                    rtf_keyword kw(++buf_in);
//                                    if (in_title && kw.is_control_char() && kw.control_char() == '\'')
//                                        title += char_by_code(buf_in);
//                                    else if (kw.keyword()==rtf_keyword::rkw_title)
//                                        in_title=true;
//                                    break;
//                                }
//                                case '{':
//                                    ++depth; ++buf_in;
//                                    break;
//                                case '}':
//                                    --depth; ++buf_in;
//                                    in_title=false;
//                                    break;
//                                default:
//                                    if (in_title)
//                                        title += *buf_in;
//                                    ++buf_in;
//                                    break;
//                                }
//                            }
//                            break;
//                        }
//                            // color table
//                        case rtf_keyword::rkw_colortbl:
//                        {
//                            color clr;
//                            while (*buf_in!='}')
//                            {
//                                switch (*buf_in)
//                                {
//                                case '\\':
//                                {
//                                    rtf_keyword kw(++buf_in);
//                                    switch (kw.keyword())
//                                    {
//                                    case rtf_keyword::rkw_red:
//                                        clr.r=kw.parameter();
//                                        break;
//                                    case rtf_keyword::rkw_green:
//                                        clr.g=kw.parameter();
//                                        break;
//                                    case rtf_keyword::rkw_blue:
//                                        clr.b=kw.parameter();
//                                        break;
//                                    }
//                                    break;
//                                }
//                                case ';':
//                                    colortbl.push_back(clr);
//                                    ++buf_in;
//                                    break;
//                                default:
//                                    ++buf_in;
//                                    break;
//                                }
//                            }
//                            ++buf_in;
//                            break;
//                        }
//                            // font table
//                        case rtf_keyword::rkw_fonttbl:
//                        {
//                            font fnt;
//                            int font_num;
//                            bool full_name=false;
//                            bool in_font=false;
//                            while (! (*buf_in=='}' && !in_font))
//                            {
//                                switch (*buf_in)
//                                {
//                                case '\\':
//                                {
//                                    rtf_keyword kw(++buf_in);
//                                    if (kw.is_control_char() && kw.control_char()=='*')
//                                        skip_group(buf_in);
//                                    else
//                                        switch (kw.keyword())
//                                        {
//                                        case rtf_keyword::rkw_f:
//                                            font_num=kw.parameter();
//                                            break;
//                                        case rtf_keyword::rkw_fprq:
//                                            fnt.pitch=kw.parameter();
//                                            break;
//                                        case rtf_keyword::rkw_fcharset:
//                                            fnt.charset=kw.parameter();
//                                            break;
//                                        case rtf_keyword::rkw_fnil:
//                                            fnt.family=font::ff_none;
//                                            break;
//                                        case rtf_keyword::rkw_froman:
//                                            fnt.family=font::ff_serif;
//                                            break;
//                                        case rtf_keyword::rkw_fswiss:
//                                            fnt.family=font::ff_sans_serif;
//                                            break;
//                                        case rtf_keyword::rkw_fmodern:
//                                            fnt.family=font::ff_monospace;
//                                            break;
//                                        case rtf_keyword::rkw_fscript:
//                                            fnt.family=font::ff_cursive;
//                                            break;
//                                        case rtf_keyword::rkw_fdecor:
//                                            fnt.family=font::ff_fantasy;
//                                            break;
//                                        }
//                                    break;
//                                }
//                                case '{':
//                                    in_font=true;
//                                    ++buf_in;
//                                    break;
//                                case '}':
//                                    in_font=false;
//                                    fonttbl.insert(std::make_pair(font_num, fnt));
//                                    fnt=font();
//                                    full_name=false;
//                                    ++buf_in;
//                                    break;
//                                case ';':
//                                    full_name=true;
//                                    ++buf_in;
//                                    break;
//                                default:
//                                    if (!full_name && in_font)
//                                        fnt.name+=*buf_in;
//                                    ++buf_in;
//                                    break;
//                                }
//                            }
//                            ++buf_in;
//                            break;
//                        }
//                            // special characters
//                        case rtf_keyword::rkw_line: case rtf_keyword::rkw_softline:
//                            par_html.write("<br>");
//                            break;
//                        case rtf_keyword::rkw_tab:
//                            par_html.write("&nbsp;&nbsp;");  // maybe, this can be done better
//                            break;
//                        case rtf_keyword::rkw_enspace: case rtf_keyword::rkw_emspace:
//                            par_html.write("&nbsp;");
//                            break;
//                        case rtf_keyword::rkw_qmspace:
//                            par_html.write("&thinsp;");
//                            break;
//                        case rtf_keyword::rkw_endash:
//                            par_html.write("&ndash;");
//                            break;
//                        case rtf_keyword::rkw_emdash:
//                            par_html.write("&mdash;");
//                            break;
//                        case rtf_keyword::rkw_bullet:
//                            par_html.write("&bull;");
//                            break;
//                        case rtf_keyword::rkw_lquote:
//                            par_html.write("&lsquo;");
//                            break;
//                        case rtf_keyword::rkw_rquote:
//                            par_html.write("&rsquo;");
//                            break;
//                        case rtf_keyword::rkw_ldblquote:
//                            par_html.write("&ldquo;");
//                            break;
//                        case rtf_keyword::rkw_rdblquote:
//                            par_html.write("&rdquo;");
//                            break;
//                            // paragraph formatting
//                        case rtf_keyword::rkw_ql:
//                            cur_options.papAlign=formatting_options::align_left;
//                            break;
//                        case rtf_keyword::rkw_qr:
//                            cur_options.papAlign=formatting_options::align_right;
//                            break;
//                        case rtf_keyword::rkw_qc:
//                            cur_options.papAlign=formatting_options::align_center;
//                            break;
//                        case rtf_keyword::rkw_qj:
//                            cur_options.papAlign=formatting_options::align_justify;
//                            break;
//                        case rtf_keyword::rkw_fi:
//                            cur_options.papFirst=(int)rint(kw.parameter()/20);
//                            break;
//                        case rtf_keyword::rkw_li:
//                            cur_options.papLeft=(int)rint(kw.parameter()/20);
//                            break;
//                        case rtf_keyword::rkw_ri:
//                            cur_options.papRight=(int)rint(kw.parameter()/20);
//                            break;
//                        case rtf_keyword::rkw_sb:
//                            cur_options.papBefore=(int)rint(kw.parameter()/20);
//                            break;
//                        case rtf_keyword::rkw_sa:
//                            cur_options.papAfter=(int)rint(kw.parameter()/20);
//                            break;
//                        case rtf_keyword::rkw_pard:
//                            cur_options.papBefore=cur_options.papAfter=0;
//                            cur_options.papLeft=cur_options.papRight=0;
//                            cur_options.papFirst=0;
//                            cur_options.papAlign=formatting_options::align_left;
//                            cur_options.papInTbl=false;
//                            break;
//                        case rtf_keyword::rkw_par: case rtf_keyword::rkw_sect:
//                            t_str=cur_options.get_par_str()+par_html.str()
//                                    +"&nbsp;"+par_html.close()+"</p>\n";
//                            if (!bInTable)
//                            {
//                                html+=t_str;
//                            }
//                            else
//                            {
//                                if (cur_options.papInTbl)
//                                {
//                                    tcCurCell->Text+=t_str;
//                                }
//                                else
//                                {
//                                    html+=tblCurTable->make()+t_str;
//                                    bInTable=false;
//                                    delete tblCurTable;
//                                    tblCurTable=new table;
//                                }
//                            }
//                            par_html.clear();
//                            break;
//                            // character formatting
//                        case rtf_keyword::rkw_super:
//                            cur_options.chpVAlign=
//                                    kw.parameter()==0?formatting_options::va_normal
//                                                    :formatting_options::va_sup;
//                            break;
//                        case rtf_keyword::rkw_sub:
//                            cur_options.chpVAlign=
//                                    kw.parameter()==0?formatting_options::va_normal
//                                                    :formatting_options::va_sub;
//                            break;
//                        case rtf_keyword::rkw_b:
//                            cur_options.chpBold=!(kw.parameter()==0);
//                            break;
//                        case rtf_keyword::rkw_caps:
//                            cur_options.chpAllCaps=!(kw.parameter()==0);
//                            break;
//                        case rtf_keyword::rkw_i:
//                            cur_options.chpItalic=!(kw.parameter()==0);
//                            break;
//                        case rtf_keyword::rkw_ul:
//                            cur_options.chpUnderline=!(kw.parameter()==0);
//                            break;
//                        case rtf_keyword::rkw_ulnone:
//                            cur_options.chpUnderline=false;
//                            break;
//                        case rtf_keyword::rkw_fs:
//                            cur_options.chpFontSize=kw.parameter();
//                            break;
//                        case rtf_keyword::rkw_dn:
//                            cur_options.chpVShift = kw.parameter() == -1 ? 6 : kw.parameter();
//                            break;
//                        case rtf_keyword::rkw_up:
//                            cur_options.chpVShift = kw.parameter() == -1 ? -6 : -kw.parameter();
//                            break;
//                        case rtf_keyword::rkw_cf:
//                            cur_options.chpFColor=colortbl[kw.parameter()];
//                            break;
//                        case rtf_keyword::rkw_cb:
//                            cur_options.chpBColor=colortbl[kw.parameter()];
//                            break;
//                        case rtf_keyword::rkw_highlight:
//                            cur_options.chpHighlight=kw.parameter();
//                            break;
//                        case rtf_keyword::rkw_f:
//                            cur_options.chpFont=fonttbl[kw.parameter()];
//                            break;
//                        case rtf_keyword::rkw_plain:
//                            cur_options.chpBold=cur_options.chpAllCaps
//                                    =cur_options.chpItalic=cur_options.chpUnderline=false;
//                            cur_options.chpVAlign=formatting_options::va_normal;
//                            cur_options.chpFontSize=cur_options.chpHighlight=0;
//                            cur_options.chpFColor=cur_options.chpBColor=color();
//                            cur_options.chpFont=font();
//                            break;
//                            // table formatting
//                        case rtf_keyword::rkw_intbl:
//                            cur_options.papInTbl=true;
//                            break;
//                        case rtf_keyword::rkw_trowd:
//                            CurCellDefs=CellDefsList.insert(CellDefsList.end(),
//                                                            table_cell_defs());
//                        case rtf_keyword::rkw_row:
//                            if (!trCurRow->Cells.empty())
//                            {
//                                trCurRow->CellDefs=CurCellDefs;
//                                if (trCurRow->Left==-1000)
//                                    trCurRow->Left=iLastRowLeft;
//                                if (trCurRow->Height==-1000)
//                                    trCurRow->Height=iLastRowHeight;
//                                tblCurTable->push_back(trCurRow);
//                                trCurRow=new table_row;
//                            }
//                            bInTable=true;
//                            break;
//                        case rtf_keyword::rkw_cell:
//                            t_str=cur_options.get_par_str()+par_html.str()
//                                    +"&nbsp;"+par_html.close()+"</p>\n";
//                            tcCurCell->Text+=t_str;
//                            par_html.clear();
//                            trCurRow->Cells.push_back(tcCurCell);
//                            tcCurCell=new table_cell;
//                            break;
//                        case rtf_keyword::rkw_cellx:
//                            tcdCurCellDef->Right=kw.parameter();
//                            CurCellDefs->push_back(tcdCurCellDef);
//                            tcdCurCellDef=new table_cell_def;
//                            break;
//                        case rtf_keyword::rkw_trleft:
//                            trCurRow->Left=kw.parameter();
//                            iLastRowLeft=kw.parameter();
//                            break;
//                        case rtf_keyword::rkw_trrh:
//                            trCurRow->Height=kw.parameter();
//                            iLastRowHeight=kw.parameter();
//                            break;
//                        case rtf_keyword::rkw_clvmgf:
//                            tcdCurCellDef->FirstMerged=true;
//                            break;
//                        case rtf_keyword::rkw_clvmrg:
//                            tcdCurCellDef->Merged=true;
//                            break;
//                        case rtf_keyword::rkw_clbrdrb:
//                            tcdCurCellDef->BorderBottom=true;
//                            tcdCurCellDef->ActiveBorder=&(tcdCurCellDef->BorderBottom);
//                            break;
//                        case rtf_keyword::rkw_clbrdrt:
//                            tcdCurCellDef->BorderTop=true;
//                            tcdCurCellDef->ActiveBorder=&(tcdCurCellDef->BorderTop);
//                            break;
//                        case rtf_keyword::rkw_clbrdrl:
//                            tcdCurCellDef->BorderLeft=true;
//                            tcdCurCellDef->ActiveBorder=&(tcdCurCellDef->BorderLeft);
//                            break;
//                        case rtf_keyword::rkw_clbrdrr:
//                            tcdCurCellDef->BorderRight=true;
//                            tcdCurCellDef->ActiveBorder=&(tcdCurCellDef->BorderRight);
//                            break;
//                        case rtf_keyword::rkw_brdrnone:
//                            if (tcdCurCellDef->ActiveBorder!=NULL)
//                            {
//                                *(tcdCurCellDef->ActiveBorder)=false;
//                            }
//                            break;
//                        case rtf_keyword::rkw_clvertalt:
//                            tcdCurCellDef->VAlign=table_cell_def::valign_top;
//                            break;
//                        case rtf_keyword::rkw_clvertalc:
//                            tcdCurCellDef->VAlign=table_cell_def::valign_center;
//                            break;
//                        case rtf_keyword::rkw_clvertalb:
//                            tcdCurCellDef->VAlign=table_cell_def::valign_bottom;
//                            break;
//                            // page formatting
//                        case rtf_keyword::rkw_paperw:
//                            iDocWidth=kw.parameter();
//                            break;
//                        case rtf_keyword::rkw_margl:
//                            iMarginLeft=kw.parameter();
//                            break;
//                        }
//                    }
//                }
//                break;
//            }
//            case '{':
//                // perform group opening actions here
//                foStack.push(cur_options);
//                ++buf_in;
//                break;
//            case '}':
//                // perform group closing actions here
//                cur_options=foStack.top();
//                foStack.pop();
//                ++buf_in;
//                break;
//            case 13: case 10:
//                ++buf_in;
//                break;
//            case '<':
//                par_html.write("&lt;");
//                ++buf_in;
//                break;
//            case '>':
//                par_html.write("&gt;");
//                ++buf_in;
//                break;
//                /*      case ' ':
//         par_html.write("&ensp;");
//         ++buf_in;
//         break;*/
//            default:
//                par_html.write(*buf_in++);
//            }
//        }

//        //   strResult = std::string("<html>\n<head>\n<STYLE type=\"text/css\">\nbody {padding-left:")
//        //           + std::string(rint(iMarginLeft/20)) + "pt;width:" + std::string(rint((iDocWidth/20))) + "pt}\n"
//        //           + "p {margin-top:0pt;margin-bottom:0pt}\n" + formatting_options::get_styles() + "</STYLE>\n"
//        //           + "<title>" + title + "</title>\n</head>\n"
//        //           + "<body>\n" + html + "</body>\n</html>";

//        strResult = std::string("<html>\n<head>\n<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\">")
//                + "<title>" + title + "</title>\n</head>\n"
//                + "<body>" + html + "</body>\n</html>\n";

//        delete tcCurCell;
//        delete trCurRow;
//        delete tblCurTable;
//        delete tcdCurCellDef;
//        return 0;
//    }
//    catch (std::exception &e)
//    {
//        std::cerr<<"Error: "<<e.what()<<std::endl;
//    }
//    catch (...)
//    {
//        std::cerr<<"Something really bad happened!";
//    }

//    return 0;
//}



//BOOL WizRtf2Html(const char* rtfText, CStringW& textResult)

int rtf2html(const char *rtfText, std::string& textResult)
{
//    if (0 != qstrnicmp(rtfText, "{\\rtf", 5))
//    {
//        WizLoadUnicodeTextFromBuffer(rtfText, strlen(rtfText), textResult);
//        //
//        return WizConvertTextToHTML_DefaultTemplate(_T(""), textResult);
//    }
     //
    try
    {
        std::string str_in(rtfText);
        std::string::iterator buf_in=str_in.begin(), buf_in_end=str_in.end();
        colorvect colortbl;
        fontmap fonttbl;
        std::string title;

        bool bAsterisk=false;
        fo_stack foStack;
        formatting_options cur_options;
        std::string html;
        html_text par_html(cur_options);

        /* CellDefs in rtf are really queer. We'll keep a list of them in main()
        and will give an iterator into this list to a row */
        table_cell_defs_list CellDefsList;
        table_cell_defs_list::iterator CurCellDefs;
        table_cell_def *tcdCurCellDef=new table_cell_def;
        table_cell *tcCurCell=new table_cell;
        table_row *trCurRow=new table_row;
        table *tblCurTable=new table;
        int iLastRowLeft=0, iLastRowHeight=0;
        std::string t_str;
        //
        int nCharToSkip = 0;
        int nNumberAfterUnicodeChar = 0;

        bool bInTable=false;
        int iDocWidth=12240;
        int iMarginLeft=1800;
        while(buf_in!=buf_in_end)
        {
            switch (*buf_in)
            {
            case '\\':
                {
                    rtf_keyword kw(++buf_in);
                    if (kw.is_control_char())
                    {
                        switch (kw.control_char())
                        {
                        case '\\': case '{': case '}':
                            par_html.write(kw.control_char());
                            break;
                        case '\'':
                            {
                                std::string stmp(1,*buf_in++);
                                stmp+=*buf_in++;
                                int code=std::strtol(stmp.c_str(), NULL, 16);
                                //switch (code)
                                //{
                                //case 167:
                                //	par_html.write("&bull;");
                                //	break;
                                //case 188:
                                //	par_html.write("&hellip;");
                                //	break;
                                //default:
                                if (nCharToSkip > 0)
                                {
                                    nCharToSkip--;
                                }
                                else
                                {
                                    par_html.write((char)code);
                                }
                                //}
                                break;
                            }
                        case '*':
                            bAsterisk=true;
                            break;
                        case '~':
                            par_html.write("&nbsp;");
                            break;
                        }
                    }
                    else //kw.is_control_char
                        if (bAsterisk)
                        {
                            bAsterisk=false;
                            skip_group(buf_in);
                        }
                        else
                        {
                            switch (kw.keyword())
                            {
                            case rtf_keyword::rkw_filetbl:
                            case rtf_keyword::rkw_stylesheet:
                            case rtf_keyword::rkw_header:
                            case rtf_keyword::rkw_footer: case rtf_keyword::rkw_headerf:
                            case rtf_keyword::rkw_footerf: case rtf_keyword::rkw_pict:
                            case rtf_keyword::rkw_object:
                                // we'll skip such groups
                                skip_group(buf_in);
                                break;
                                // document title
                            case rtf_keyword::rkw_info:
                                {
                                    int depth=1;
                                    bool in_title=false;
                                    while (depth>0)
                                    {
                                        //                     std::cout<<std::string(buf_in).substr(0,20)<<"\t"<<depth<<std::endl;
                                        switch (*buf_in)
                                        {
                                        case '\\':
                                            {
                                                rtf_keyword kw(++buf_in);
                                                if (kw.keyword()==rtf_keyword::rkw_title)
                                                    in_title=true;
                                                break;
                                            }
                                        case '{': ++depth; ++buf_in; break;
                                        case '}': --depth; ++buf_in; in_title=false; break;
                                        default: if (in_title) title+=*buf_in; ++buf_in; break;
                                        }
                                    }
                                    break;
                                }
                                // color table
                            case rtf_keyword::rkw_colortbl:
                                {
                                    color clr;
                                    clr.r = 0;
                                    clr.g = 0;
                                    clr.b = 0;
                                    while (*buf_in!='}')
                                    {
                                        switch (*buf_in)
                                        {
                                        case '\\':
                                            {
                                                rtf_keyword kw(++buf_in);
                                                switch (kw.keyword())
                                                {
                                                case rtf_keyword::rkw_red:
                                                    clr.r=kw.parameter();
                                                    break;
                                                case rtf_keyword::rkw_green:
                                                    clr.g=kw.parameter();
                                                    break;
                                                case rtf_keyword::rkw_blue:
                                                    clr.b=kw.parameter();
                                                    break;
                                                default:
                                                    break;
                                                }
                                                break;
                                            }
                                        case ';':
                                            colortbl.push_back(clr);
                                            ++buf_in;
                                            break;
                                        default:
                                            ++buf_in;
                                            break;
                                        }
                                    }
                                    ++buf_in;
                                    break;
                                }
                                // font table
                            case rtf_keyword::rkw_fonttbl:
                                {
                                    font fnt;
                                    int font_num;
                                    bool full_name=false;
                                    bool in_font=false;
                                    while (! (*buf_in=='}' && !in_font))
                                    {
                                        switch (*buf_in)
                                        {
                                        case '\\':
                                            {
                                                rtf_keyword kw(++buf_in);
                                                if (kw.is_control_char() && kw.control_char()=='*')
                                                {
                                                    skip_group(buf_in);
                                                }
                                                else if (kw.is_control_char() && kw.control_char()=='\'')
                                                {
                                                    if (!full_name && in_font)
                                                    {
                                                        fnt.name+=ConvertHexChar(buf_in);
                                                    }
                                                }
                                                else
                                                {
                                                    switch (kw.keyword())
                                                    {
                                                    case rtf_keyword::rkw_f:
                                                        font_num=kw.parameter();
                                                        break;
                                                    case rtf_keyword::rkw_fprq:
                                                        fnt.pitch=kw.parameter();
                                                        break;
                                                    case rtf_keyword::rkw_fcharset:
                                                        fnt.charset=kw.parameter();
                                                        break;
                                                    case rtf_keyword::rkw_fnil:
                                                        fnt.family=font::ff_none;
                                                        break;
                                                    case rtf_keyword::rkw_froman:
                                                        fnt.family=font::ff_serif;
                                                        break;
                                                    case rtf_keyword::rkw_fswiss:
                                                        fnt.family=font::ff_sans_serif;
                                                        break;
                                                    case rtf_keyword::rkw_fmodern:
                                                        fnt.family=font::ff_monospace;
                                                        break;
                                                    case rtf_keyword::rkw_fscript:
                                                        fnt.family=font::ff_cursive;
                                                        break;
                                                    case rtf_keyword::rkw_fdecor:
                                                        fnt.family=font::ff_fantasy;
                                                        break;
                                                    default:
                                                        break;
                                                    }
                                                }
                                                break;
                                            }
                                        case '{':
                                            in_font=true;
                                            ++buf_in;
                                            break;
                                        case '}':
                                            in_font=false;
                                            fonttbl.insert(std::make_pair(font_num, fnt));
                                            fnt=font();
                                            full_name=false;
                                            ++buf_in;
                                            break;
                                        case ';':
                                            full_name=true;
                                            ++buf_in;
                                            break;
                                        default:
                                            if (!full_name && in_font)
                                                fnt.name+=*buf_in;
                                            ++buf_in;
                                            break;
                                        }
                                    }
                                    ++buf_in;
                                    break;
                                }
                                // special characters
                            case rtf_keyword::rkw_line: case rtf_keyword::rkw_softline:
                                par_html.write("<br>");
                                break;
                            case rtf_keyword::rkw_tab:
                                for (int i = 0; i < GetTabSize(); i++)
                                {
                                    par_html.write("&nbsp;");  // maybe, this can be done better
                                }
                                break;
                            case rtf_keyword::rkw_enspace: case rtf_keyword::rkw_emspace:
                                par_html.write("&nbsp;");
                                break;
                            case rtf_keyword::rkw_qmspace:
                                par_html.write("&thinsp;");
                                break;
                            case rtf_keyword::rkw_endash:
                                par_html.write("&ndash;");
                                break;
                            case rtf_keyword::rkw_emdash:
                                par_html.write("&mdash;");
                                break;
                            case rtf_keyword::rkw_bullet:
                                par_html.write("&bull;");
                                break;
                            case rtf_keyword::rkw_lquote:
                                par_html.write("&lsquo;");
                                break;
                            case rtf_keyword::rkw_rquote:
                                par_html.write("&rsquo;");
                                break;
                            case rtf_keyword::rkw_ldblquote:
                                par_html.write("&ldquo;");
                                break;
                            case rtf_keyword::rkw_rdblquote:
                                par_html.write("&rdquo;");
                                break;
                                // paragraph formatting
                            case rtf_keyword::rkw_ql:
                                cur_options.papAlign=formatting_options::align_left;
                                break;
                            case rtf_keyword::rkw_qr:
                                cur_options.papAlign=formatting_options::align_right;
                                break;
                            case rtf_keyword::rkw_qc:
                                cur_options.papAlign=formatting_options::align_center;
                                break;
                            case rtf_keyword::rkw_qj:
                                cur_options.papAlign=formatting_options::align_justify;
                                break;
                            case rtf_keyword::rkw_fi:
                                cur_options.papFirst=(int)rint(kw.parameter()/20);
                                break;
                            case rtf_keyword::rkw_li:
                                cur_options.papLeft=(int)rint(kw.parameter()/20);
                                break;
                            case rtf_keyword::rkw_ri:
                                cur_options.papRight=(int)rint(kw.parameter()/20);
                                break;
                            case rtf_keyword::rkw_sb:
                                cur_options.papBefore=(int)rint(kw.parameter()/20);
                                break;
                            case rtf_keyword::rkw_sa:
                                cur_options.papAfter=(int)rint(kw.parameter()/20);
                                break;
                            case rtf_keyword::rkw_pard:
                                cur_options.papBefore=cur_options.papAfter=0;
                                cur_options.papLeft=cur_options.papRight=0;
                                cur_options.papFirst=0;
                                cur_options.papAlign=formatting_options::align_left;
                                cur_options.papInTbl=false;
                                break;
                            case rtf_keyword::rkw_par: case rtf_keyword::rkw_sect:
                                t_str=cur_options.get_par_str()+par_html.str()
                                    +par_html.close()+"</div>\n";
                                if (!bInTable)
                                {
                                    html+=t_str;
                                }
                                else
                                {
                                    if (cur_options.papInTbl)
                                    {
                                        tcCurCell->Text+=t_str;
                                    }
                                    else
                                    {
                                        html+=tblCurTable->make()+t_str;
                                        bInTable=false;
                                        delete tblCurTable;
                                        tblCurTable=new table;
                                    }
                                }
                                par_html.clear();
                                break;
                                // character formatting
                            case rtf_keyword::rkw_super:
                                cur_options.chpVAlign=
                                    kw.parameter()==0?formatting_options::va_normal
                                    :formatting_options::va_sup;
                                break;
                            case rtf_keyword::rkw_sub:
                                cur_options.chpVAlign=
                                    kw.parameter()==0?formatting_options::va_normal
                                    :formatting_options::va_sub;
                                break;
                            case rtf_keyword::rkw_b:
                                cur_options.chpBold=!(kw.parameter()==0);
                                break;
                            case rtf_keyword::rkw_i:
                                cur_options.chpItalic=!(kw.parameter()==0);
                                break;
                            case rtf_keyword::rkw_ul:
                                cur_options.chpUnderline=!(kw.parameter()==0);
                                break;
                            case rtf_keyword::rkw_ulnone:
                                cur_options.chpUnderline=false;
                                break;
                            case rtf_keyword::rkw_fs:
                                cur_options.chpFontSize=kw.parameter();
                                break;
                            case rtf_keyword::rkw_cf:
                                if (colortbl.size() > size_t(kw.parameter())
                                    && kw.parameter() >= 0)
                                {
                                    cur_options.chpFColor=colortbl[kw.parameter()];
                                }
                                break;
                            case rtf_keyword::rkw_cb:
                                if (colortbl.size() > size_t(kw.parameter())
                                    && kw.parameter() >= 0)
                                {
                                    cur_options.chpBColor=colortbl[kw.parameter()];
                                }
                                break;
                            case rtf_keyword::rkw_highlight:
                                cur_options.chpHighlight=kw.parameter();
                                break;
                            case rtf_keyword::rkw_f:
                                if (fonttbl.size() > size_t(kw.parameter())
                                    && kw.parameter() >= 0)
                                {
                                    cur_options.chpFont=fonttbl[kw.parameter()];
                                }
                                //
                                //par_html.
                                {
//                                    char szCharset[100] = {0};
//                                    //std::itoa(cur_options.chpFont.charset, szCharset, 10);
//                                    //sprintf();
//                                    //szCharset = QString::number(cur_options.chpFont.charset).toUtf8().constData();
//                                    QByteArray ba = QString::number(cur_options.chpFont.charset).toUtf8();
//                                    strncpy(szCharset, ba.constData(), ba.length());
                                 //   itoa_s(cur_options.chpFont.charset, szCharset, 100, 10);
                                    //
                                    par_html.writeHiddenText("<!--WizRtf2Html Charset=UTF-8");
//                                    par_html.writeHiddenText(szCharset);
                                    par_html.writeHiddenText("  -->");
                                }
                                //
                                //
                                //
                                break;
                            case rtf_keyword::rkw_plain:
                                cur_options.chpBold=cur_options.chpItalic
                                    =cur_options.chpUnderline=false;
                                cur_options.chpVAlign=formatting_options::va_normal;
                                cur_options.chpFontSize=cur_options.chpHighlight=0;
                                cur_options.chpFColor=cur_options.chpBColor=color();
                                cur_options.chpFont=font();
                                break;
                                // table formatting
                            case rtf_keyword::rkw_intbl:
                                cur_options.papInTbl=true;
                                break;
                            case rtf_keyword::rkw_trowd:
                                CurCellDefs=CellDefsList.insert(CellDefsList.end(),
                                    table_cell_defs());
                            case rtf_keyword::rkw_row:
                                if (!trCurRow->Cells.empty())
                                {
                                    trCurRow->CellDefs=CurCellDefs;
                                    if (trCurRow->Left==-1000)
                                        trCurRow->Left=iLastRowLeft;
                                    if (trCurRow->Height==-1000)
                                        trCurRow->Height=iLastRowHeight;
                                    tblCurTable->push_back(trCurRow);
                                    trCurRow=new table_row;
                                }
                                bInTable=true;
                                break;
                            case rtf_keyword::rkw_cell:
                                t_str=cur_options.get_par_str()+par_html.str()
                                    +"&nbsp;"+par_html.close()+"</p>\n";
                                tcCurCell->Text+=t_str;
                                par_html.clear();
                                trCurRow->Cells.push_back(tcCurCell);
                                tcCurCell=new table_cell;
                                break;
                            case rtf_keyword::rkw_cellx:
                                tcdCurCellDef->Right=kw.parameter();
                                CurCellDefs->push_back(tcdCurCellDef);
                                tcdCurCellDef=new table_cell_def;
                                break;
                            case rtf_keyword::rkw_trleft:
                                trCurRow->Left=kw.parameter();
                                iLastRowLeft=kw.parameter();
                                break;
                            case rtf_keyword::rkw_trrh:
                                trCurRow->Height=kw.parameter();
                                iLastRowHeight=kw.parameter();
                                break;
                            case rtf_keyword::rkw_clvmgf:
                                tcdCurCellDef->FirstMerged=true;
                                break;
                            case rtf_keyword::rkw_clvmrg:
                                tcdCurCellDef->Merged=true;
                                break;
                            case rtf_keyword::rkw_clbrdrb:
                                tcdCurCellDef->BorderBottom=true;
                                tcdCurCellDef->ActiveBorder=&(tcdCurCellDef->BorderBottom);
                                break;
                            case rtf_keyword::rkw_clbrdrt:
                                tcdCurCellDef->BorderTop=true;
                                tcdCurCellDef->ActiveBorder=&(tcdCurCellDef->BorderTop);
                                break;
                            case rtf_keyword::rkw_clbrdrl:
                                tcdCurCellDef->BorderLeft=true;
                                tcdCurCellDef->ActiveBorder=&(tcdCurCellDef->BorderLeft);
                                break;
                            case rtf_keyword::rkw_clbrdrr:
                                tcdCurCellDef->BorderRight=true;
                                tcdCurCellDef->ActiveBorder=&(tcdCurCellDef->BorderRight);
                                break;
                            case rtf_keyword::rkw_brdrnone:
                                if (tcdCurCellDef->ActiveBorder!=NULL)
                                {
                                    *(tcdCurCellDef->ActiveBorder)=false;
                                }
                                break;
                            case rtf_keyword::rkw_clvertalt:
                                tcdCurCellDef->VAlign=table_cell_def::valign_top;
                                break;
                            case rtf_keyword::rkw_clvertalc:
                                tcdCurCellDef->VAlign=table_cell_def::valign_center;
                                break;
                            case rtf_keyword::rkw_clvertalb:
                                tcdCurCellDef->VAlign=table_cell_def::valign_bottom;
                                break;
                                // page formatting
                            case rtf_keyword::rkw_paperw:
                                iDocWidth=kw.parameter();
                                break;
                            case rtf_keyword::rkw_margl:
                                iMarginLeft=kw.parameter();
                                break;
                            case rtf_keyword::rkw_unicodechar:
                                {
                                    std::string strChar;
                                    CString strParam = WizIntToStr((unsigned short)(kw.parameter()));
                                    strChar = std::string("&#") + strParam.toStdString() + ";";
                                    par_html.write(strChar);
                                    //
                                    if (buf_in != buf_in_end)
                                    {
                                        if (*buf_in == ' ')
                                        {
                                            buf_in++;
                                        }
                                    }
                                    if (buf_in != buf_in_end)
                                    {
                                        if (*buf_in == '?')
                                        {
                                            buf_in++;
                                            nNumberAfterUnicodeChar = 0;
                                        }
                                        else
                                        {
                                            nCharToSkip = nNumberAfterUnicodeChar;
                                        }
                                    }
                                    //
                                }
                                break;
                            case rtf_keyword::rkw_unicodecounter:
                                {
                                    nNumberAfterUnicodeChar = kw.parameter();
                                }
                                break;
                            default:
                                break;
                            }
                        }
                        break;
                }
            case '{':
                // perform group opening actions here
                foStack.push(cur_options);
                ++buf_in;
                break;
            case '}':
                // perform group closing actions here
                if (!foStack.empty())
                {
                    cur_options=foStack.top();
                    foStack.pop();
                }
                ++buf_in;
                break;
            case 13: case 10:
                ++buf_in;
                break;
            case '<':
                par_html.write("&lt;");
                ++buf_in;
                break;
            case '>':
                par_html.write("&gt;");
                ++buf_in;
                break;
                /*      case ' ':
                par_html.write("&ensp;");
                ++buf_in;
                break;*/
            default:
                if (*buf_in == ' ')
                {
                    par_html.write("&nbsp;");
                    buf_in++;
                }
                else if (*buf_in == '\t')
                {
                    for (int i = 0; i < GetTabSize(); i++)
                    {
                        par_html.write("&nbsp;");  // maybe, this can be done better
                    }
                    buf_in++;
                }
                else
                {
                    par_html.write(*buf_in++);
                }
            }
        }
        //
        if (!par_html.str().empty())
        {
            html += par_html.str();
            html += par_html.close();
        }
        //
        int nDefaultCharset = 0;
        if (!fonttbl.empty())
        {
            nDefaultCharset = fonttbl[0].charset;
        }
        //
        textResult = std::string("<html>\n<head>\n<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\">")
            + "<title>" + title + "</title>\n</head>\n"
            + "<body>" + html + "</body>\n</html>\n";
        //

        //
        delete tcCurCell;
        delete trCurRow;
        delete tblCurTable;
        delete tcdCurCellDef;
        //
        return TRUE;
    }
    catch (std::exception& /*&e*/)
    {
        //std::cerr<<"Error: "<<e.what()<<std::endl;
    }
    catch (...)
    {
        //std::cerr<<"Something really bad happened!";
    }
    //
    return FALSE;
}
