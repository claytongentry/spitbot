defmodule ScraperTest do
  use ExUnit.Case
  doctest Scraper

  setup do
    bypass      = Bypass.open
    config      = Application.get_env :scraper, Scraper
    endpoint    = "http://localhost:#{bypass.port}"
    lyrics_file = "./test/support/test.txt"
    new_config  =
      config
      |> Keyword.put(:endpoint, endpoint)
      |> Keyword.put(:lyrics_file, lyrics_file)

    Application.put_env :scraper, Scraper, new_config

    on_exit fn ->
      File.rm lyrics_file
      Application.put_env :scraper, Scraper, config

      :ok
    end

    {:ok, bypass: bypass}
  end

  test "client requests correctly", %{bypass: bypass} do
    Bypass.expect bypass, fn conn ->
      assert conn.method       == "GET"
      assert conn.request_path == "/fake.method.get"
      assert conn.query_string == "apikey=#{config[:api_key]}" <>
                                  "&fake_param=fake_value"

      Plug.Conn.send_resp conn, 200, Poison.encode!(%{"data" => "fake_data"})
    end

    response = Scraper.get "/fake.method.get", %{"fake_param" => "fake_value"}

    assert response = %HTTPoison.Response{body: %{"data" => "fake_data"}}
  end

  test "writes correctly" do
    Scraper.write "test lyrics\nmore test lyrics\n" <>
                  "******* NOT FOR COMMERCIAL USE\n(1928470)"

    assert "test lyrics\nmore test lyrics\n" == File.read! config[:lyrics_file]
  end

  defp config, do: Application.get_env(:scraper, Scraper)
end
