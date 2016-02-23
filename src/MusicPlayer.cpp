#include "MusicPlayer.h"

MusicPlayer::MusicPlayer()
: m_volume(50.f)
{

	m_filenames[Music::MenuTheme] = "res/music/AgentSix_TrevorLentz.ogg";
	m_filenames[Music::GameTheme] = "res/music/JustMove_TrevorLentz.ogg";

}

void MusicPlayer::play(Music::ID theme) {
	
	std::string filename = m_filenames[theme];

	if (!m_music.openFromFile(filename))
		throw std::runtime_error("Music " + filename + " could not be loaded.");

	m_music.setVolume(m_volume);
	m_music.setLoop(true);
	m_music.play();

}
void MusicPlayer::stop() {
	m_music.stop();
}

void MusicPlayer::setPaused(const bool paused) {
	
	if (paused)
		m_music.pause();
	else
		m_music.play();

}
void MusicPlayer::setVolume(const float volume) {

	m_music.setVolume(volume);
	m_volume = volume;

}