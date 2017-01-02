defmodule Scraper.Album do
  alias Scraper.Track

  @moduledoc """
  Exposes an interface for processing album data
  via the MusixMatch API.
  """

  @allowed_get_params   ~w(album_id format)
  @allowed_track_params ~w(album_id album_mbid format
                           f_has_lyrics page page_size)

  @doc """
  Fetches data for a given album
  """
  def get(params) do
    Scraper.get "/album.get", Map.take(params, @allowed_get_params)
  end

  @doc """
  Fetches all tracks for a given album
  """
  def tracks(params) do
    Scraper.get "/album.tracks.get", Map.take(params, @allowed_track_params)
  end

  @doc """
  Fetches the lyrics for all songs in a given album
  """
  def fetch_lyrics(album) do
    album
    |> Map.fetch!("track_list")
    |> Enum.map(&Track.lyrics/1)
  end
end
