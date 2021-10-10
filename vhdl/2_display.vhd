-- display (a, b, c, d, e, f, g, dp)

-- UPALI_SVE D2 D1 D0   S7(A) S6(B) S5(C) S4(D) S3(E) S2(F) S1(G) S0(DP)
--  1        x  x  x    1      1     1     1     1     1     1     1
--  0        0  0  0    1      1     1     1     1     1     0     0
--  0        0  0  1    0      1     1     0     0     0     0     0
--  0        0  1  0    1      1     0     1     1     0     1     0
--  0        0  1  1    1      1     1     1     0     0     1     0
--  0        1  0  0    0      1     1     0     0     1     1     0
--  0        1  0  1    1      0     1     1     0     1     1     0
--  0        1  1  0    1      0     1     1     1     1     1     0
--  0        1  1  1    1      1     1     0     0     0     0     0

library IEEE;
use IEEE.std_logic_vector.all;

entity display_decoder is
    port (
        ulaz : in std_logic_vector(2 downto 0); -- 2^n, n = 3, 8 mogucih vrijednosti
        upali_sve: in std_logic; -- upali sve segmente
        izlaz: out std_logic_vector(7 downto 0); -- 7segmentni display + decimalna tocka

    ); 
end display_decoder;

architecture Behavioral of display_decoder is
    begin
        process (ulaz, upali_sve)
            begin
                if (upali_sve = not '1') then
                    izlaz <= not "11111111"
                elsif (ulaz = not 'xxx') then
                    izlaz <= not "xxxxxxx0"; -- itd za sve segmente
                end if;
        end process;

end Behavioral;

