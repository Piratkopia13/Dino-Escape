#include "MusicPlayer.h"

MusicPlayer::MusicPlayer()
: m_volume(50.f)
{

	// Map filenames to IDs
	m_filenames[Music::MenuTheme] = "res/music/AgentSix_TrevorLentz.ogg";
	m_filenames[Music::GameTheme] = "res/music/JustMove_TrevorLentz.ogg";

}

void MusicPlayer::play(Music::ID id) {
	
	// Get the filename of the id
	std::string& filename = m_filenames[id];

	// Check if the open failed
	if (!m_music.openFromFile(filename))
		throw std::logic_error("Music " + filename + " could not be loaded.");

	// Set the volume
	m_music.setVolume(m_volume);
	// Set it up to loop
	m_music.setLoop(true);

	// Play the music
	m_music.play();

}
void MusicPlayer::stop() {
	// Stop the music
	m_music.stop();
}

void MusicPlayer::setPaused(const bool paused) {
	
	// Play or pause the music
	if (paused)
		m_music.pause();
	else
		m_music.play();

}
void MusicPlayer::setVolume(const float volume) {

	// Update the currently playing music
	m_music.setVolume(volume);
	// Update the volume member variable
	m_volume = volume;

}