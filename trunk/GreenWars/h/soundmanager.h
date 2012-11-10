#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <IwString.h> 
#include <IwList.h>

struct sound
{
	char name[256];
	char *pBuffer;
	int length;
};

class CSoundManager
{
	CIwList<sound> m_sounds;
public:
	CSoundManager(void);
	~CSoundManager(void);

	void LoadSounds(char * configFile);

	void Play(char * trackName);

private:
	void Clear();
};

#endif SOUNDMANAGER_H