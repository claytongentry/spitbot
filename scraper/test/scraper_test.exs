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

  test "client requests correctly", %{bypass: bypass} do
    Bypass.expect bypass, &handle_request/1

    response = Scraper.get "/fake.method.get", %{"fake_param" => "fake_value"}

    assert response = %HTTPoison.Response{body: %{"data" => "fake_data"}}
  end

  test "gets lucky artist", %{bypass: bypass} do
    Bypass.expect bypass, &handle_request/1

    Scraper.get_lucky "Prodigy", :artist

    lyrics = File.read! config[:lyrics_file]
    assert Regex.match? ~r/Now and then I think of when we were together/, lyrics
  end

  test "gets lucky track", %{bypass: bypass} do
    Bypass.expect bypass, &handle_request/1

    Scraper.get_lucky "Somebody that I used to know", :track

    assert "Now and then I think of when we were together\r\n...\n" == File.read! config[:lyrics_file]
  end

  test "writes correctly" do
    Scraper.write "test lyrics\nmore test lyrics\n" <>
                  "******* NOT FOR COMMERCIAL USE *******\n(1928470)"

    assert "test lyrics\nmore test lyrics\n" == File.read! config[:lyrics_file]
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
  defp do_handle_request(%{request_path: "/fake.method.get"} = conn) do
    json = Poison.encode! %{"data" => "fake_data"}

    {:ok, {200, json}}
  end
  defp do_handle_request(conn) do
    {:ok, {404, ""}}
  end

  defp config, do: Application.get_env(:scraper, Scraper)
end
