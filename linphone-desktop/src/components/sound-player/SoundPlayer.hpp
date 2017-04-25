/*
 * SoundPlayer.hpp
 * Copyright (C) 2017  Belledonne Communications, Grenoble, France
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *  Created on: April 25, 2017
 *      Author: Ronan Abhamon
 */

#ifndef SOUND_PLAYER_H_
#define SOUND_PLAYER_H_

#include <memory>

#include <QObject>

// =============================================================================

namespace linphone {
  class Player;
}

class SoundPlayer : public QObject {
  Q_OBJECT;

  Q_PROPERTY(QString source READ getSource WRITE setSource NOTIFY sourceChanged);
  Q_PROPERTY(PlaybackState playbackState READ getPlaybackState WRITE setPlaybackState NOTIFY playbackStateChanged);
  Q_PROPERTY(int duration READ getDuration NOTIFY sourceChanged);

public:
  enum PlaybackState {
    PlayingState,
    PausedState,
    StoppedState,
    ErrorState
  };

  Q_ENUM(PlaybackState);

  SoundPlayer (QObject *parent = Q_NULLPTR);
  ~SoundPlayer () = default;

  void pause ();
  void play ();
  void stop ();

  void seek (int offset);

  int getPosition () const;

signals:
  void sourceChanged (const QString &source);

  void paused ();
  void playing ();
  void stopped ();

  void playbackStateChanged (PlaybackState playbackState);

private:
  void setError (const QString &message);

  QString getSource () const;
  void setSource (const QString &source);

  PlaybackState getPlaybackState () const;
  void setPlaybackState (PlaybackState playbackState);

  int getDuration () const;

  std::shared_ptr<linphone::Player> mInternalPlayer;
  QString mSource;
  PlaybackState mPlaybackState = StoppedState;
};

#endif // SOUND_PLAYER_H_