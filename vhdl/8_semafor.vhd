library ieee;
use ieee.std_logic_1164.all;
 -- crveno, crveno_zuta, zelena, zuta redoslijed
entity semafor is
    port(
        reset, clk: in std_logic;
        izlaz: out std_logic_vector(2 downto 0);

    );
end semafor;

architecture semafor_beh of semafor is
    type stanje is (crveno, crveno_zuta, zelena, zuta);
    signal cur_state : stanje := crveno;
    signal next_state : stanje;
    begin 
        process (reset, clk)
            begin
                if (reset = '1') then
                    cur_state <= crveno;
                elsif (clk'event and clk = '1') then
                    cur_state <= next_state;
                end if;
        end process;

        process (cur_state, clk)
                    begin
                        if (clk'event and clk = '1') then
                            if (cur_state = crveno) then
                                next_state <= crveno_zuta;
                                y <= "001";
                            elsif (cur_state = crveno_zuta) then
                                next_state <= zelena;
                                y <= "011";
                            elsif (cur_state = zelena) then
                                next_state <= zuta;
                                y <= "100";
                            elsif (cur_state = zuta) then
                                next_state <= crvena;
                                y <= "010";
                            end if;
                        end if;
        end process;

