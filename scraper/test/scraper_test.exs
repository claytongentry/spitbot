defmodule ScraperTest do
  use ExUnit.Case
  doctest Scraper

  setup do
    bypass     = Bypass.open
    config     = Application.get_env :scraper, Scraper
    endpoint   = "http://localhost:#{bypass.port}"
    new_config = Keyword.put config, :endpoint, endpoint
    Application.put_env :scraper, Scraper, new_config

    on_exit fn ->
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

    Scraper.get "/fake.method.get", %{"fake_param" => "fake_value"}

    assert {:ok, %HTTPoison.Response{body: %{"data" => "fake_data"}}}
  end

  defp config, do: Application.get_env(:scraper, Scraper)
end
