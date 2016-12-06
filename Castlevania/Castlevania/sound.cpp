#include "Sound.h"

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib" )

DSound::DSound(HWND hWnd)
	: pDirectSound(NULL),
	pPrimaryBuffer(NULL)
{
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;
	DirectSoundCreate8(NULL, &pDirectSound, NULL);

	// Set the cooperative level to priority so the format of the primary sound buffer can be modified.
	pDirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY);

	// Setup the primary buffer description.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Get control of the primary sound buffer on the default sound device.
	pDirectSound->CreateSoundBuffer(&bufferDesc, &pPrimaryBuffer, NULL);

	// Setup the format of the primary sound bufffer.
	// In this case it is a .WAV file recorded at 44,100 samples per second in 16-bit stereo (cd audio format).
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// Set the primary buffer to be the wave format specified.
	pPrimaryBuffer->SetFormat(&waveFormat);
}

DSound::~DSound()
{
	if (pPrimaryBuffer)
	{
		pPrimaryBuffer->Release();
		pPrimaryBuffer = NULL;
	}
	if (pDirectSound)
	{
		pDirectSound->Release();
		pDirectSound = NULL;
	}
}

// must be 44.1k 16bit Stereo PCM Wave
Sound DSound::CreateSound(char* wavFileName)
{
	int error;
	FILE* filePtr;
	unsigned int count;
	WaveHeaderType waveFileHeader;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;
	HRESULT result;
	IDirectSoundBuffer* tempBuffer;
	IDirectSoundBuffer8* pSecondaryBuffer;
	unsigned char* waveData;
	unsigned char* bufferPtr;
	unsigned long bufferSize;


	// Open the wave file in binary.
	fopen_s(&filePtr, wavFileName, "rb");

	// Read in the wave file header.
	fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);

	// Set the wave format of secondary buffer that this wave file will be loaded onto.
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	if (strcmp(wavFileName, "Data\\Sound\\Round1.wav") == 0 || strcmp(wavFileName, "Data\\Sound\\Round2.wav") == 0 || strcmp(wavFileName, "Data\\Sound\\Round3.wav") == 0)
		waveFileHeader.dataSize = 9990000;

	// Set the buffer description of the secondary sound buffer that the wave file will be loaded onto.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Create a temporary sound buffer with the specific buffer settings.
	pDirectSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);

	// Test the buffer format against the direct sound 8 interface and create the secondary buffer.
	tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&pSecondaryBuffer);

	// Release the temporary buffer.
	tempBuffer->Release();
	tempBuffer = 0;

	// Move to the beginning of the wave data which starts at the end of the data chunk header.
	fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);

	// Create a temporary buffer to hold the wave file data.
	waveData = new unsigned char[waveFileHeader.dataSize];

	// Read in the wave file data into the newly created buffer.
	fread(waveData, 1, waveFileHeader.dataSize, filePtr);

	// Close the file once done reading.
	fclose(filePtr);

	// Lock the secondary buffer to write wave data into it.
	pSecondaryBuffer->Lock(0, waveFileHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);

	// Copy the wave data into the buffer.
	memcpy(bufferPtr, waveData, waveFileHeader.dataSize);

	// Unlock the secondary buffer after the data has been written to it.
	pSecondaryBuffer->Unlock((void*)bufferPtr, bufferSize, NULL, 0);

	// Release the wave data since it was copied into the secondary buffer.
	delete[] waveData;
	waveData = NULL;

	return Sound(pSecondaryBuffer);
}

Sound::Sound(IDirectSoundBuffer8* pSecondaryBuffer)
	: pBuffer(pSecondaryBuffer)
{}

Sound::Sound()
	: pBuffer(NULL)
{}

Sound::Sound(const Sound& base)
	: pBuffer(base.pBuffer)
{
	pBuffer->AddRef();
}

Sound::~Sound()
{
	if (pBuffer)
	{
		pBuffer->Release();
		pBuffer = NULL;
	}
}

const Sound& Sound::operator=(const Sound& rhs)
{
	this->~Sound();
	pBuffer = rhs.pBuffer;
	pBuffer->AddRef();
	return rhs;
}

// attn is the attenuation value in units of 0.01 dB (larger 
// negative numbers give a quieter sound, 0 for full volume)
void Sound::Play(int attn)
{
	attn = max(attn, DSBVOLUME_MIN);
	HRESULT result;

	// Set position at the beginning of the sound buffer.
	pBuffer->SetCurrentPosition(0);

	// Set volume of the buffer to attn
	pBuffer->SetVolume(attn);

	// Play the contents of the secondary sound buffer.
	pBuffer->Play(0, 0, 0);

}

void Sound::PlayRepeat(int attn)
{
	attn = max(attn, DSBVOLUME_MIN);
	HRESULT result;

	// Set position at the beginning of the sound buffer.
	pBuffer->SetCurrentPosition(0);


	// Set volume of the buffer to attn
	pBuffer->SetVolume(attn);

	// Play the contents of the secondary sound buffer.
	pBuffer->Play(0, 0, DSBPLAY_LOOPING);
}

void Sound::Stop()
{
	pBuffer->Stop();
}