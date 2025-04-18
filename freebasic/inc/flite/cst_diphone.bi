'' FreeBASIC binding for flite-2.0.0-release
''
'' based on the C header files:
''                     Language Technologies Institute                      
''                        Carnegie Mellon University                        
''                         Copyright (c) 1999-2014                          
''                           All Rights Reserved.                           
''                                                                          
''     Permission is hereby granted, free of charge, to use and distribute  
''     this software and its documentation without restriction, including   
''     without limitation the rights to use, copy, modify, merge, publish,  
''     distribute, sublicense, and/or sell copies of this work, and to      
''     permit persons to whom this work is furnished to do so, subject to   
''     the following conditions:                                            
''      1. The code must retain the above copyright notice, this list of    
''         conditions and the following disclaimer.                         
''      2. Any modifications must be clearly marked as such.                
''      3. Original authors' names are not deleted.                         
''      4. The authors' names are not used to endorse or promote products   
''         derived from this software without specific prior written        
''         permission.                                                      
''                                                                          
''     CARNEGIE MELLON UNIVERSITY AND THE CONTRIBUTORS TO THIS WORK         
''     DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING      
''     ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT   
''     SHALL CARNEGIE MELLON UNIVERSITY NOR THE CONTRIBUTORS BE LIABLE      
''     FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES    
''     WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN   
''     AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,          
''     ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF       
''     THIS SOFTWARE.                                                       
''
'' translated to FreeBASIC by:
''   FreeBASIC development team

#pragma once

#include once "cst_file.bi"
#include once "cst_val.bi"
#include once "cst_features.bi"
#include once "cst_wave.bi"
#include once "cst_track.bi"
#include once "cst_sts.bi"
#include once "cst_hrg.bi"

extern "C"

#define _CST_DIPHONE_H__

type cst_diphone_entry_struct
	name as const zstring ptr
	start_pm as ushort
	pb_pm as ubyte
	end_pm as ubyte
end type

type cst_diphone_entry as cst_diphone_entry_struct

type cst_diphone_db_struct
	name as const zstring ptr
	num_entries as long
	diphones as const cst_diphone_entry ptr
	sts as const cst_sts_list ptr
end type

type cst_diphone_db as cst_diphone_db_struct
extern cst_val_type_diphone_db as const long
declare function val_diphone_db(byval v as const cst_val ptr) as cst_diphone_db ptr
declare function diphone_db_val(byval v as const cst_diphone_db ptr) as cst_val ptr
declare function diphone_synth(byval utt as cst_utterance ptr) as cst_utterance ptr
declare function get_diphone_units(byval utt as cst_utterance ptr) as cst_utterance ptr

end extern
