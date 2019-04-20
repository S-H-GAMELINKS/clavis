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
    refute_nil @clavis = Clavis.new("3000")
    assert @clavis.port == "3000"
  end
end
