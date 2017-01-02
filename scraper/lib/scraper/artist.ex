defmodule Scraper.Artist do

  @moduledoc """
  Exposes an interface for processing artist data
  via the MusixMatch API.
  """

  @allowed_album_params  ~w(artist_id artist_mbid g_album_name s_release_date
                            page page_size format)
  @allowed_get_params     ~w(artist_id artist_mbid format)
  @allowed_related_params ~w(artist_id artist_mbid page page_size format)
  @allowed_search_params  ~w(q_artist f_artist_id f_artist_mbid
                             page page_size format)

  @doc """
  Fetches data for a given artist
  """
  def get(params) do
    Scraper.get "/artist.get", Map.take(params, @allowed_get_params)
  end

  @doc """
  Searches for an artist according to the
  supplied parameters
  """
  def search(params) do
    Scraper.get "/artist.search", Map.take(params, @allowed_search_params)
  end

  @doc """
  Fetches album data for the given artist
  """
  def albums(params) do
    Scraper.get "/artist.albums.get", Map.take(params, @allowed_album_params)
  end

  @doc """
  Fetches artists related to the given artist
  """
  def related(params) do
    Scraper.get "/artist.related.get", Map.take(params, @allowed_related_params)
  end
end
