defmodule Scraper.Artist do

  @allowed_album_params  ~w(artist_id artist_mbid g_album_name s_release_date
                            page page_size format)
  @allowed_get_params     ~w(artist_id artist_mbid format)
  @allowed_related_params ~w(artist_id artist_mbid page page_size format)
  @allowed_search_params  ~w(q_artist f_artist_id f_artist_mbid
                             page page_size format)

  def get(params) do
    Scraper.get "/artist.get", Map.take(params, @allowed_get_params)
  end

  def search(params) do
    Scraper.get "/artist.search", Map.take(params, @allowed_search_params)
  end

  def albums(params) do
    Scraper.get "/artist.albums.get", Map.take(params, @allowed_album_params)
  end

  def related(params) do
    Scraper.get "/artist.related.get", Map.take(params, @allowed_related_params)
  end
end
