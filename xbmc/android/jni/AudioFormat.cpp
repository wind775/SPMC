/*
 *      Copyright (C) 2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "AudioFormat.h"
#include "JNIBase.h"
#include "jutils/jutils-details.hpp"

using namespace jni;

int CJNIAudioFormat::ENCODING_PCM_16BIT = 0x00000002;
int CJNIAudioFormat::CHANNEL_OUT_STEREO = 0x0000000c;
int CJNIAudioFormat::CHANNEL_OUT_5POINT1 = 0x000000fc;
int CJNIAudioFormat::CHANNEL_OUT_7POINT1 = 0x000003fc;

// OUYA-specific
int CJNIAudioFormat::ENCODING_IEC61937_16BIT = -1;

void CJNIAudioFormat::PopulateStaticFields()
{
  int sdk = CJNIBase::GetSDKVersion();
  if (sdk >= 3)
  {
    jhclass c = find_class("android/media/AudioFormat");
    CJNIAudioFormat::ENCODING_PCM_16BIT = get_static_field<int>(c, "ENCODING_PCM_16BIT");
    if (sdk >= 5)
    {
      CJNIAudioFormat::CHANNEL_OUT_STEREO = get_static_field<int>(c, "CHANNEL_OUT_STEREO");
      CJNIAudioFormat::CHANNEL_OUT_5POINT1 = get_static_field<int>(c, "CHANNEL_OUT_5POINT1");
      CJNIAudioFormat::CHANNEL_OUT_7POINT1 = get_static_field<int>(c, "CHANNEL_OUT_7POINT1");
    }

    // OUYA-specific
    jfieldID id = get_static_field_id<jclass>(c, "ENCODING_IEC61937_16BIT", "I");
    if (id != NULL)
      CJNIAudioFormat::ENCODING_IEC61937_16BIT = get_static_field<int>(c, "ENCODING_IEC61937_16BIT");
    else
      xbmc_jnienv()->ExceptionClear();
  }
}

