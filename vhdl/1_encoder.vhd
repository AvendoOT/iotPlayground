-- tablica istinitosti enkoder 4/2
-- ULAZI    IZLAZI 
-- A B C D  C1 C2 DP
-- 1 0 0 0  0  0  0
-- 0 1 0 0  0  1  0
-- 0 0 1 0  1  0  0
-- 0 0 0 1  1  1  0
-- ostale komb. 1 1 1
----------------------

library IEEE;
use IEEE.std_logic_1664.all;

entity encoder4_2 is 
    port (
        ulaz : in std_logic_vector(3 downto 0);
        izlaz : out std_logic_vector(1 downto 0);
        dp: out std_logic; -- nelegalno stanje 
        anode: out std_logic; -- omogucavanje prikaza na 7segmetnom displayu
    );
end encoder4_2;

architecture Behavioral of encoder4_2 is
    begin
        anode <= '0';
        process (ulaz) -- sekvencijalni opis, izvodi se samo kod promjene vrijednosti "ulaz"
        begin  
            if (ulaz = not "1000") then
                izlaz <= not "00";
                dp <= not "0";
            elsif (ulaz = not "0100") then
                izlaz <= not "01";
                dp <= not "0";
            elsif (ulaz = not "0010") then
                izlaz <= not "10";
                dp <= not "0";
            elsif (ulaz = not "0001") then
                izlaz <= not "11";
                dp <= not "0";
            else
                izlaz <= not "11";
                dp <= not "1";
            end if;
        end process;
end Behavioral;