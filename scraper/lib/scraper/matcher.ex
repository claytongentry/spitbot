defmodule Scraper.Matcher do

  @moduledoc """
  Exposes an interface for searching the MusixMatch API
  """

  @allowed_lyrics_params   ~w(q_track q_artist format)
  @allowed_subtitle_params ~w(q_track q_artist f_subtitle_length
                              f_subtitle_length_max_deviation format)
  @allowed_track_params    ~w(q_track q_artist q_album format
                              f_has_lyrics f_has_subtitle)
  def lyrics(params) do
    Scraper.get "/matcher.lyrics.get", Map.take(params, @allowed_lyrics_params)
  end

  def subtitle(params) do
    Scraper.get "/matcher.subtitle.get", Map.take(params, @allowed_subtitle_params)
  end

  def track(params) do
    Scraper.get "/matcher.track.get", Map.take(params, @allowed_track_params)
  end
end
