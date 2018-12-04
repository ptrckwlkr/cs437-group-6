#include "MusicManager.h"

MusicManager music;

void MusicManager::setMusic(std::string track) {
	if (initialized) {
		this->bg_music->stop();
	} else {
		this->initialized = true;
	}
	this->bg_music = resources.GetMusic(track);
	this->bg_music->setLoop(true);
	this->curTrack = track;
}

void MusicManager::setVolume(float volume) {
	if (this->initialized) this->bg_music->setVolume(volume);
}

void MusicManager::playMusic() {
	if (this->initialized) this->bg_music->play();
}

void MusicManager::stopMusic() {
	if (this->initialized) this->bg_music->stop();
}

std::string MusicManager::getCurrentTrack() {
	return this->curTrack;
}
