require "test_helper"
require "clavis/clavis"

class ClavisTest < Minitest::Test
  def test_that_it_has_a_version_number
    refute_nil ::Clavis::VERSION
  end

  def test_init
    refute_nil Clavis.new
  end

  def run_method_defined
    assert Clavis.method_defined?("run")
  end

  def test_set_port
    refute_nil @clavis = Clavis.new
    @clavis.set_port("3000")
    assert(@clavis.port == "3000")
  end

  def test_set_route_and_response
    refute_nil @clavis = Clavis.new
    assert @clavis.set_route("/", "hoge", "text/plain")
    assert(@clavis["/"] == "hoge")
  end

  def test_set_default_routes
    refute_nil @clavis = Clavis.new
    assert(@clavis["/"] == "Hello Clavis!\n Enjoy Your Ruby Web dev!")
  end

  def test_set_default_port
    refute_nil @clavis = Clavis.new
    assert(@clavis.port == "3000")
  end

  def test_set_content_type
    refute_nil @clavis = Clavis.new
    assert @clavis.set_route("/", "<h1>Hoge</h1>", "text/html")
    assert(@clavis["/"] == "<h1>Hoge</h1>")
  end
end
