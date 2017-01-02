defmodule ScraperTest do
  use ExUnit.Case
  doctest Scraper

  setup do
    bypass     = Bypass.open
    config     = Application.get_env(:scraper, Scraper)
    new_config =
      Keyword.merge config, [
        endpoint: "http://localhost:#{bypass.port}",
        lyrics_file: "./test/support/test.txt"
      ]

    Application.put_env :scraper, Scraper, new_config

    on_exit fn ->
      File.rm new_config[:lyrics_file]
      Application.put_env :scraper, Scraper, config

      :ok
    end

    {:ok, bypass: bypass}
  end

  test "gets lucky", %{bypass: bypass} do
    Bypass.expect bypass, &handle_request/1

    Scraper.get_lucky %{
      "q_artist" => "LMFAO",
      "q_track"  => "Sexy and I Know It"
    }

    assert "When I walk on by, girls be looking like damn he fly\r\n" <>
           "I pay to the beat, walking on the street with "           <>
           "in my new lafreak, yeah\n" == File.read! config[:lyrics_file]
  end

  defp handle_request(conn) do
    {:ok, {status_code, json}} = do_handle_request conn

    Plug.Conn.send_resp conn, status_code, json
  end

  defp do_handle_request(%{request_path: "/track.search"} = conn) do
    json = File.read! "./test/support/fixtures/track_search.json"

    assert conn.method == "GET"

    {:ok, {200, json}}
  end
  defp do_handle_request(%{request_path: "/track.lyrics.get"} = conn) do
    json = File.read! "./test/support/fixtures/track_lyrics_get.json"

    assert conn.method == "GET"

    {:ok, {200, json}}
  end
  defp do_handle_request(%{request_path: "/artist.search"} = conn) do
    json = File.read! "./test/support/fixtures/artist_search.json"

    assert conn.method == "GET"

    {:ok, {200, json}}
  end
  defp do_handle_request(%{request_path: "/artist.albums.get"} = conn) do
    json = File.read! "./test/support/fixtures/artist_albums.json"

    assert conn.method == "GET"

    {:ok, {200, json}}
  end
  defp do_handle_request(%{request_path: "/album.tracks.get"} = conn) do
    json = File.read! "./test/support/fixtures/album_tracks.json"

    assert conn.method == "GET"

    {:ok, {200, json}}
  end
  defp do_handle_request(%{request_path: "/matcher.lyrics.get"} = conn) do
    json = File.read! "./test/support/fixtures/matcher_lyrics.json"

    assert conn.method == "GET"

    {:ok, {200, json}}
  end
  defp do_handle_request(conn) do
    {:ok, {404, "{}"}}
  end

  defp config, do: Application.get_env(:scraper, Scraper)
end
