defmodule Scraper do
  use HTTPoison.Base
  require Logger

  alias Scraper.{Album, Artist, Track}

  @moduledoc """
  Exposes an interface for scraping the Genius API
  and adding lyrics to the JeezyAI lyrics bank
  """

  @doc """
  Makes a request to the MusixMatch API using
  the given method and params
  """
  def get(method, opts \\ %{}) do
    opts = Map.put opts, "apikey", config[:api_key]

    get!(method, [], params: opts).body
  end

  @doc """
  Gets the lyrics related to the first search result

  If an artist, gets lyrics for all tracks of all the artist's albums.
  If a track, gets lyrics for the track
  """
  def get_lucky(q_artist, :artist) do
    %{"artist_list" => [ %{"artist" => artist} | _ ]} =
      %{"q_artist" => q_artist, "page_size" => 1}
      |> Artist.search

    artist
    |> Artist.albums
    |> Map.fetch!("album_list")
    |> Stream.map(&Album.tracks &1["album"] )
    |> Enum.map(&Album.fetch_lyrics/1)
    |> List.flatten
    |> Stream.map(&extract_lyrics/1)
    |> Enum.each(&write/1)
  end
  def get_lucky(q_track, :track) do
    %{"track_list" => [ %{"track" => track} | _ ]} =
      %{"q_track" => q_track, "page_size" => 1}
      |> Track.search

    track
    |> Track.lyrics
    |> extract_lyrics
    |> write
  end

  @doc """
  Appends lyrics line-by-line to lyrics file
  """
  def write(lyrics) do
    File.open config[:lyrics_file], ~w(binary append)a, &do_write(&1, lyrics)
  end

  defp do_write(device, lyrics) do
    lyrics
    |> String.split("\n")
    |> Stream.reject(&is_invalid/1)
    |> Enum.each(&IO.write(device, "#{&1}\n"))
  end

  defp extract_lyrics(%{"lyrics" => %{"lyrics_body" => lyrics}}), do: lyrics
  defp extract_lyrics(data) do
    Logger.error "Could not extract lyrics from: #{inspect data}"
  end

  defp is_invalid(line), do: Regex.match? ~r/\*{7}|(\d)/, line

  # Overwrite HTTPoison callbacks
  defp process_url(url),            do: config[:endpoint] <> url
  defp process_response_body(body)  do
    body
    |> Poison.decode!
    |> get_in(~w(message body))
  end

  defp config, do: Application.get_env :scraper, __MODULE__
end
