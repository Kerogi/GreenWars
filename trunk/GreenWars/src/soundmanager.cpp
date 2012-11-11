#include "soundmanager.h"
#include "s3eMemory.h"
#include "s3eSound.h"
#include "json_parser.h"

CSoundManager::CSoundManager(void)
{
	s3eSoundSetInt(S3E_SOUND_DEFAULT_FREQ, 24000);
}


CSoundManager::~CSoundManager(void)
{
	Clear();
}

int getFileSize(const char * fileName)
{
	s3eFile * fileHandle = s3eFileOpen(fileName, "rb");
	int fileSize = s3eFileGetSize(fileHandle);
	s3eFileClose(fileHandle);
	return fileSize;
}

int readFile(const char * fileName, void * buffer, int length)
{
	s3eFile * fileHandle = s3eFileOpen(fileName, "rb");
	int fileSize = s3eFileRead(buffer, 1, length, fileHandle);
	s3eFileClose(fileHandle);
	return fileSize;
}

/// TODO Ugly solution. Shoud be replced
sound * g_pCurrentParsedPair;

int json_callback(void* ctx, int type, const struct JSON_value_struct* value)
{
	CIwList<sound> *pSoundList = (CIwList<sound>*)ctx;

	switch(type) {
	case JSON_T_KEY:
		g_pCurrentParsedPair = new sound;
		strcpy(g_pCurrentParsedPair->name, value->vu.str.value);
		break;   
	case JSON_T_STRING:
		g_pCurrentParsedPair->length = getFileSize(value->vu.str.value);
		g_pCurrentParsedPair->pBuffer =  (char *)s3eMallocBase(g_pCurrentParsedPair->length);
		readFile(value->vu.str.value, g_pCurrentParsedPair->pBuffer, g_pCurrentParsedPair->length);
		pSoundList->append(*g_pCurrentParsedPair);
		break;
	default:
		// TDOD parser error
		break;
	}

	return 1;
}

void CSoundManager::LoadSounds(char * configFile)
{
	int fileSize = getFileSize(configFile);
	char * pConfigFileText = (char *)s3eMallocBase(fileSize);
	readFile(configFile, pConfigFileText, fileSize);

	JSON_config jconf;
	init_JSON_config(&jconf);
	jconf.allow_comments = 1;
	jconf.callback = json_callback;
	jconf.callback_ctx = &m_sounds;

	Clear();

	JSON_parser jparser = new_JSON_parser(&jconf);

	for (int i = 0; i<fileSize; ++i) {
		int next_char = pConfigFileText[i];
		if (next_char <= 0) {
			break;
		}
		if (!JSON_parser_char(jparser, next_char)) {
			delete_JSON_parser(jparser);
			s3eFreeBase (pConfigFileText);
			// TODO Error processing
			return;
		}
	}

	if (!JSON_parser_done(jparser)) {
		delete_JSON_parser(jparser);
		s3eFreeBase (pConfigFileText);
		// TODO Error processing
		return;
	}

	s3eFreeBase(pConfigFileText);
}

void CSoundManager::Clear()
{
	CIwList<sound>::iterator iSound = m_sounds.begin();
	for(;iSound != m_sounds.end(); iSound++)
	{
		s3eFreeBase(iSound->pBuffer);
	}
	m_sounds.clear();
}

void CSoundManager::Play(char * trackName)
{
	CIwList<sound>::iterator iSound = m_sounds.begin();
	for(;iSound != m_sounds.end(); iSound++)
	{
		if(stricmp(iSound->name, trackName) == 0)
		{
			int channel = s3eSoundGetFreeChannel();
			if(channel >= 0)// Skip sound if no chanel
			{
				if (s3eSoundChannelPlay(channel, (int16 *)iSound->pBuffer, iSound->length/2, 1, 0) == S3E_RESULT_ERROR)
				{
					//TODO error play
				}
				else
				{
					// OK
				}
			}
			return;
		}
	}


}