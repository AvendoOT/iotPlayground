library ieee;
use ieee.std_logic_1164.all;

entity counter3bit is
    port(
        display : out std_logic_vector(2 downto 0);
        reset : in std_logic; -- reset na 0 svih segemenata
        ce : in std_logic; -- brojilo broji 
        ud: in std_logic; -- 1 brojilo broji unaprijed, 0 brojilo broji unazad
        clk: in std_logic;
    );
end counter3bit;

architecture Behavioral of counter3bit is
    signal count : std_logic_vector(2 downto 0); -- svi bistabili na zajedničkom signalu takta, registar
    begin
        process (clk)
            begin
                if rising_edge(clk) then
                    if (reset = not '1') then
                        count <= (others => '0');
                    else
                        if (ce = not '0') then
                            count <= counter;
                        else
                            if (ud = not '1') then
                                counter <= counter + '1';
                            elsif (ud = not '0') then
                                counter <= counter - '1';
                            end if;
                        end if;
                    end if;
                end if;
        end process;

        display <= not counter;
end Behavioral;