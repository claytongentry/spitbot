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

  defp handle_request(%{request_path: "/track.search"} = conn) do
    json =
      Path.join(__DIR__, "support/fixtures/track_search.json")
      |> File.read!

    assert conn.method == "GET"

    Plug.Conn.send_resp conn, 200, json
  end
  defp handle_request(%{request_path: "/track.lyrics.get"} = conn) do
    json =
      Path.join(__DIR__, "support/fixtures/track_lyrics_get.json")
      |> File.read!

    assert conn.method == "GET"

    Plug.Conn.send_resp conn, 200, json
  end
  defp handle_request(%{request_path: "/fake.method.get"} = conn) do
    json = Poison.encode! %{"data" => "fake_data"}

    Plug.Conn.send_resp conn, 200, json
  end
  defp handle_request(conn) do
    Plug.Conn.send_resp conn, 404
  end

  defp config, do: Application.get_env(:scraper, Scraper)
end
