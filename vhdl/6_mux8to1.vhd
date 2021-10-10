library ieee;
use ieee.std_logic_1164.all;

entity mux8to1 is
    port(
        selector : in std_logic_vector(2 downto 0);
        in_mux : std_logic_vector(7 downto 0);
        out_mux : out std_logic;
    );
end mux8to1;

architecture mux_beh of mux8to1 is
    begin
        with selector select
            out_mux <= in_mux(7) when "111",
            in_mux(6) when "110",
            in_mux(5) when "101",
            in_mux(4) when "100",
            in_mux(3) when "011",
            in_mux(2) when "010",
            in_mux(1) when "001",
            in_mux(0) when others;
    end mux_beh;
                    