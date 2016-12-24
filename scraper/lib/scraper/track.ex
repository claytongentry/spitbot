defmodule Scraper.Track do

  @allowed_get_params      ~w(track_id track_mbid format)
  @allowed_lyrics_params   ~w(track_id track_mbid format)
  @allowed_snippet_params  ~w(track_id format)
  @allowed_subtitle_params ~w(track_id track_mbid format
                              subtitle_format f_subtitle_length
                              f_subtitle_length_max_deviation)

  def get(params) do
    Scraper.get "/track.get", Map.take(params, @allowed_get_params)
  end

  def lyrics(params) do
    Scraper.get "/track.lyrics.get", Map.take(params, @allowed_get_params)
  end

  def snippet(params) do
    Scraper.get "/track.snippet.get", Map.take(params, @allowed_snippet_params)
  end

  def subtitle(params) do
    Scraper.get "/track.subtitle.get", Map.take(params, @allowed_subtitle_params)
  end
end
