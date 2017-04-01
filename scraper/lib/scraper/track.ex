defmodule Scraper.Track do

  @moduledoc """
  Exposes an interface for processing track data
  via the MusixMatch API.
  """

  @allowed_get_params      ~w(track_id track_mbid format)
  @allowed_lyrics_params   ~w(track_id track_mbid format)
  @allowed_search_params   ~w(q_track page page_size format)
  @allowed_snippet_params  ~w(track_id format)
  @allowed_subtitle_params ~w(track_id track_mbid format
                              subtitle_format f_subtitle_length
                              f_subtitle_length_max_deviation)

  @doc """
  Fetches data for the given track
  """
  def get(params) do
    Scraper.get "/track.get", Map.take(params, @allowed_get_params)
  end

  @doc """
  Fetches lyrics data for the given track
  """
  def lyrics(params) do
    Scraper.get "/track.lyrics.get", Map.take(params, @allowed_get_params)
  end

  @doc """
  Searches for a track according to the given parameters
  """
  def search(params) do
    Scraper.get "/track.search", Map.take(params, @allowed_search_params)
  end

  @doc """
  Fetches a snippet of the given track
  """
  def snippet(params) do
    Scraper.get "/track.snippet.get", Map.take(params, @allowed_snippet_params)
  end

  @doc """
  Fetches subtitles for the given track
  """
  def subtitle(params) do
    Scraper.get "/track.subtitle.get", Map.take(params, @allowed_subtitle_params)
  end
end
