/* 
 *  libpinyin
 *  Library to deal with pinyin.
 *  
 *  Copyright (C) 2011 Peng Wu <alexepico@gmail.com>
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef PINYIN_PARSER2_H
#define PINYIN_PARSER2_H

#include "chewing_key.h"
#include "pinyin_parser2.h"

namespace pinyin{

inline int pinyin_exact_compare2(const ChewingKey * key_lhs,
                                 const ChewingKey * key_rhs,
                                 int phrase_length){
    int i;
    int result;

    /* compare initial */
    for (i = 0; i < phrase_length; ++i) {
        result = key_lhs[i].m_initial - key_rhs[i].m_initial;
        if (0 != result)
            return result;
    }

    /* compare middle and final */
    for (i = 0; i < phrase_length; ++i) {
        result = key_lhs[i].m_middle - key_rhs[i].m_middle;
        if (0 != result)
            return result;
        result = key_lhs[i].m_final - key_rhs[i].m_final;
        if (0 != result)
            return result;
    }

    /* compare tone */
    for (i = 0; i < phrase_length; ++i) {
        result = key_lhs[i].m_tone - key_rhs[i].m_tone;
        if (0 != result)
            return result;
    }

    return 0;
}


inline int pinyin_compare_with_ambiguities2(guint32 options,
                                            const ChewingKey * key_lhs,
                                            const ChewingKey * key_rhs,
                                            int phrase_length){
    int i;
    int result;

    /* compare initial */
    for (i = 0; i < phrase_length; ++i) {
        result = pinyin_compare_initial2
            (options,
             (ChewingInitial)key_lhs[i].m_initial,
             (ChewingInitial)key_rhs[i].m_initial);
        if (0 != result)
            return result;
    }

    /* compare middle and final */
    for (i = 0; i < phrase_length; ++i) {
        result = pinyin_compare_middle_and_final2
            (options,
             (ChewingMiddle)key_lhs[i].m_middle,
             (ChewingMiddle)key_rhs[i].m_middle,
             (ChewingFinal) key_lhs[i].m_final,
             (ChewingFinal) key_rhs[i].m_final);
        if (0 != result)
            return result;
    }

    /* compare tone */
    for (i = 0; i < phrase_length; ++i) {
        result = pinyin_compare_tone2
            (options,
             (ChewingTone)key_lhs[i].m_tone,
             (ChewingTone)key_rhs[i].m_tone);
        if (0 != result)
            return result;
    }

    return 0;
}

};

#endif
